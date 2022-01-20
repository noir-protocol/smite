// This file is part of NOIR.
//
// Copyright (c) 2022 Haderech Pte. Ltd.
// SPDX-License-Identifier: AGPL-3.0-or-later
//
#pragma once
#include <noir/common/thread_pool.h>
#include <noir/consensus/config.h>
#include <noir/consensus/crypto.h>
#include <noir/consensus/priv_validator.h>
#include <noir/consensus/state.h>
#include <noir/consensus/types.h>

namespace noir::consensus {

/**
 * Handles execution of the consensus algorithm.
 * It processes votes and proposals, and upon reaching agreement,
 * commits blocks to the chain and executes them against the application.
 * The internal state machine receives input from peers, the internal validator, and from a timer.
 */
struct consensus_state : public std::enable_shared_from_this<consensus_state> {
  consensus_state();

  static std::unique_ptr<consensus_state> new_state(const consensus_config& cs_config_, state& state_);

  state get_state();
  int64_t get_last_height();
  std::unique_ptr<round_state> get_round_state();
  void set_priv_validator(const priv_validator& priv);
  void update_priv_validator_pub_key();
  void reconstruct_last_commit(state& state_);

  void on_start();

  void update_height(int64_t height);
  void update_round_step(int32_t rount, round_step_type step);
  void schedule_round_0(round_state& rs_);
  void update_to_state(state& state_);
  void new_step();

  void receive_routine(msg_info_ptr mi);
  void handle_msg();

  void schedule_timeout(
    std::chrono::system_clock::duration duration_, int64_t height, int32_t round, round_step_type step);
  void tick(timeout_info_ptr ti);
  void tock(timeout_info_ptr ti);
  void handle_timeout(timeout_info_ptr ti);

  void enter_new_round(int64_t height, int32_t round);

  void enter_propose(int64_t height, int32_t round);
  bool is_proposal_complete();
  bool is_proposal(p2p::bytes address);
  void decide_proposal(int64_t height, int32_t round);

  void enter_prevote(int64_t height, int32_t round);
  void enter_prevote_wait(int64_t height, int32_t round);
  void enter_precommit(int64_t height, int32_t round);
  void enter_precommit_wait(int64_t height, int32_t round);
  void enter_commit(int64_t height, int32_t round);

  void set_proposal(p2p::proposal_message& msg);
  bool add_proposal_block_part(p2p::block_part_message& msg, p2p::node_id peer_id);
  bool try_add_vote(p2p::vote_message& msg, p2p::node_id peer_id);
  bool add_vote(p2p::vote_message& msg, p2p::node_id peer_id);

  //  // config details
  //  config            *cfg.ConsensusConfig
  consensus_config cs_config;

  //  privValidator     types.PrivValidator // for signing votes
  //  privValidatorType types.PrivValidatorType
  std::optional<priv_validator> local_priv_validator;
  priv_validator_type local_priv_validator_type;

  //
  //  // store blocks and commits
  //  blockStore sm.BlockStore
  //
  //  // create and execute blocks
  //  blockExec *sm.BlockExecutor
  //
  //  // notify us if txs are available
  //  txNotifier txNotifier
  //
  //  // add evidence to the pool
  //  // when it's detected
  //  evpool evidencePool
  //

  // internal state
  //  mtx tmsync.RWMutex
  //  cstypes.RoundState
  //  state sm.State // State until height-1.
  std::mutex mtx;
  round_state rs{};
  state local_state; // State until height-1.
  //  // privValidator pubkey, memoized for the duration of one block
  //  // to avoid extra requests to HSM
  //  privValidatorPubKey crypto.PubKey
  pub_key local_priv_validator_pub_key;

  //
  //  // state changes may be triggered by: msgs from peers,
  //  // msgs from ourself, or by timeouts
  //  peerMsgQueue     chan msgInfo
  channels::peer_message_queue::channel_type& peer_mq_channel;
  channels::peer_message_queue::channel_type::handle peer_mq_subscription;

  //  internalMsgQueue chan msgInfo
  channels::internal_message_queue::channel_type& internal_mq_channel;
  channels::internal_message_queue::channel_type::handle internal_mq_subscription;

  //    timeoutTicker    TimeoutTicker
  channels::timeout_ticker::channel_type& timeout_ticker_channel;
  channels::timeout_ticker::channel_type::handle timeout_ticker_subscription;
  std::mutex timeout_ticker_mtx;
  std::unique_ptr<boost::asio::steady_timer> timeout_ticker_timer;
  uint16_t thread_pool_size = 2;
  std::optional<named_thread_pool> thread_pool;
  timeout_info_ptr old_ti;

  //
  //  // information about about added votes and block parts are written on this channel
  //  // so statistics can be computed by reactor
  //  statsMsgQueue chan msgInfo
  //
  //  // we use eventBus to trigger msg broadcasts in the reactor,
  //  // and to notify external subscribers, eg. through a websocket
  //  eventBus *types.EventBus
  //
  //  // a Write-Ahead Log ensures we can recover from any kind of crash
  //  // and helps us avoid signing conflicting votes
  //  wal          WAL
  //    replayMode   bool // so we don't log signing errors during replay
  //  doWALCatchup bool // determines if we even try to do the catchup
  //
  //  // for tests where we want to limit the number of transitions the state makes
  //  nSteps int
  int n_steps;

  //
  //  // some functions can be overwritten for testing
  //  decideProposal func(height int64, round int32)
  //  doPrevote      func(height int64, round int32)
  //  setProposal    func(proposal *types.Proposal) error
  ///-- directly implemented decide_proposal
  ///-- directly implemented set_proposal

  //
  //  // closed when we finish shutting down
  //  done chan struct{}
  //
  //  // synchronous pubsub between consensus state and reactor.
  //  // state only emits EventNewRoundStep and EventVote
  //  evsw tmevents.EventSwitch
  //
  //  // for reporting metrics
  //  metrics *Metrics
  //
  //  // wait the channel event happening for shutting down the state gracefully
  //  onStopCh chan *cstypes.RoundState
};

} // namespace noir::consensus
