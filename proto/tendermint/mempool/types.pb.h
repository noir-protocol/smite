// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tendermint/mempool/types.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_tendermint_2fmempool_2ftypes_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_tendermint_2fmempool_2ftypes_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_tendermint_2fmempool_2ftypes_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_tendermint_2fmempool_2ftypes_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_tendermint_2fmempool_2ftypes_2eproto;
namespace tendermint {
namespace mempool {
class Message;
struct MessageDefaultTypeInternal;
extern MessageDefaultTypeInternal _Message_default_instance_;
class Txs;
struct TxsDefaultTypeInternal;
extern TxsDefaultTypeInternal _Txs_default_instance_;
}  // namespace mempool
}  // namespace tendermint
PROTOBUF_NAMESPACE_OPEN
template<> ::tendermint::mempool::Message* Arena::CreateMaybeMessage<::tendermint::mempool::Message>(Arena*);
template<> ::tendermint::mempool::Txs* Arena::CreateMaybeMessage<::tendermint::mempool::Txs>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace tendermint {
namespace mempool {

// ===================================================================

class Txs final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tendermint.mempool.Txs) */ {
 public:
  inline Txs() : Txs(nullptr) {}
  ~Txs() override;
  explicit constexpr Txs(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Txs(const Txs& from);
  Txs(Txs&& from) noexcept
    : Txs() {
    *this = ::std::move(from);
  }

  inline Txs& operator=(const Txs& from) {
    CopyFrom(from);
    return *this;
  }
  inline Txs& operator=(Txs&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Txs& default_instance() {
    return *internal_default_instance();
  }
  static inline const Txs* internal_default_instance() {
    return reinterpret_cast<const Txs*>(
               &_Txs_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Txs& a, Txs& b) {
    a.Swap(&b);
  }
  inline void Swap(Txs* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Txs* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Txs* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Txs>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Txs& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Txs& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Txs* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tendermint.mempool.Txs";
  }
  protected:
  explicit Txs(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTxsFieldNumber = 1,
  };
  // repeated bytes txs = 1;
  int txs_size() const;
  private:
  int _internal_txs_size() const;
  public:
  void clear_txs();
  const std::string& txs(int index) const;
  std::string* mutable_txs(int index);
  void set_txs(int index, const std::string& value);
  void set_txs(int index, std::string&& value);
  void set_txs(int index, const char* value);
  void set_txs(int index, const void* value, size_t size);
  std::string* add_txs();
  void add_txs(const std::string& value);
  void add_txs(std::string&& value);
  void add_txs(const char* value);
  void add_txs(const void* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& txs() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_txs();
  private:
  const std::string& _internal_txs(int index) const;
  std::string* _internal_add_txs();
  public:

  // @@protoc_insertion_point(class_scope:tendermint.mempool.Txs)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> txs_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_tendermint_2fmempool_2ftypes_2eproto;
};
// -------------------------------------------------------------------

class Message final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tendermint.mempool.Message) */ {
 public:
  inline Message() : Message(nullptr) {}
  ~Message() override;
  explicit constexpr Message(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Message(const Message& from);
  Message(Message&& from) noexcept
    : Message() {
    *this = ::std::move(from);
  }

  inline Message& operator=(const Message& from) {
    CopyFrom(from);
    return *this;
  }
  inline Message& operator=(Message&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Message& default_instance() {
    return *internal_default_instance();
  }
  enum SumCase {
    kTxs = 1,
    SUM_NOT_SET = 0,
  };

  static inline const Message* internal_default_instance() {
    return reinterpret_cast<const Message*>(
               &_Message_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Message& a, Message& b) {
    a.Swap(&b);
  }
  inline void Swap(Message* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Message* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Message* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Message>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Message& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Message& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Message* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tendermint.mempool.Message";
  }
  protected:
  explicit Message(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTxsFieldNumber = 1,
  };
  // .tendermint.mempool.Txs txs = 1;
  bool has_txs() const;
  private:
  bool _internal_has_txs() const;
  public:
  void clear_txs();
  const ::tendermint::mempool::Txs& txs() const;
  PROTOBUF_NODISCARD ::tendermint::mempool::Txs* release_txs();
  ::tendermint::mempool::Txs* mutable_txs();
  void set_allocated_txs(::tendermint::mempool::Txs* txs);
  private:
  const ::tendermint::mempool::Txs& _internal_txs() const;
  ::tendermint::mempool::Txs* _internal_mutable_txs();
  public:
  void unsafe_arena_set_allocated_txs(
      ::tendermint::mempool::Txs* txs);
  ::tendermint::mempool::Txs* unsafe_arena_release_txs();

  void clear_sum();
  SumCase sum_case() const;
  // @@protoc_insertion_point(class_scope:tendermint.mempool.Message)
 private:
  class _Internal;
  void set_has_txs();

  inline bool has_sum() const;
  inline void clear_has_sum();

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  union SumUnion {
    constexpr SumUnion() : _constinit_{} {}
      ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized _constinit_;
    ::tendermint::mempool::Txs* txs_;
  } sum_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  uint32_t _oneof_case_[1];

  friend struct ::TableStruct_tendermint_2fmempool_2ftypes_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Txs

// repeated bytes txs = 1;
inline int Txs::_internal_txs_size() const {
  return txs_.size();
}
inline int Txs::txs_size() const {
  return _internal_txs_size();
}
inline void Txs::clear_txs() {
  txs_.Clear();
}
inline std::string* Txs::add_txs() {
  std::string* _s = _internal_add_txs();
  // @@protoc_insertion_point(field_add_mutable:tendermint.mempool.Txs.txs)
  return _s;
}
inline const std::string& Txs::_internal_txs(int index) const {
  return txs_.Get(index);
}
inline const std::string& Txs::txs(int index) const {
  // @@protoc_insertion_point(field_get:tendermint.mempool.Txs.txs)
  return _internal_txs(index);
}
inline std::string* Txs::mutable_txs(int index) {
  // @@protoc_insertion_point(field_mutable:tendermint.mempool.Txs.txs)
  return txs_.Mutable(index);
}
inline void Txs::set_txs(int index, const std::string& value) {
  txs_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set:tendermint.mempool.Txs.txs)
}
inline void Txs::set_txs(int index, std::string&& value) {
  txs_.Mutable(index)->assign(std::move(value));
  // @@protoc_insertion_point(field_set:tendermint.mempool.Txs.txs)
}
inline void Txs::set_txs(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  txs_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:tendermint.mempool.Txs.txs)
}
inline void Txs::set_txs(int index, const void* value, size_t size) {
  txs_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:tendermint.mempool.Txs.txs)
}
inline std::string* Txs::_internal_add_txs() {
  return txs_.Add();
}
inline void Txs::add_txs(const std::string& value) {
  txs_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:tendermint.mempool.Txs.txs)
}
inline void Txs::add_txs(std::string&& value) {
  txs_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:tendermint.mempool.Txs.txs)
}
inline void Txs::add_txs(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  txs_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:tendermint.mempool.Txs.txs)
}
inline void Txs::add_txs(const void* value, size_t size) {
  txs_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:tendermint.mempool.Txs.txs)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
Txs::txs() const {
  // @@protoc_insertion_point(field_list:tendermint.mempool.Txs.txs)
  return txs_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
Txs::mutable_txs() {
  // @@protoc_insertion_point(field_mutable_list:tendermint.mempool.Txs.txs)
  return &txs_;
}

// -------------------------------------------------------------------

// Message

// .tendermint.mempool.Txs txs = 1;
inline bool Message::_internal_has_txs() const {
  return sum_case() == kTxs;
}
inline bool Message::has_txs() const {
  return _internal_has_txs();
}
inline void Message::set_has_txs() {
  _oneof_case_[0] = kTxs;
}
inline void Message::clear_txs() {
  if (_internal_has_txs()) {
    if (GetArenaForAllocation() == nullptr) {
      delete sum_.txs_;
    }
    clear_has_sum();
  }
}
inline ::tendermint::mempool::Txs* Message::release_txs() {
  // @@protoc_insertion_point(field_release:tendermint.mempool.Message.txs)
  if (_internal_has_txs()) {
    clear_has_sum();
      ::tendermint::mempool::Txs* temp = sum_.txs_;
    if (GetArenaForAllocation() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    sum_.txs_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::tendermint::mempool::Txs& Message::_internal_txs() const {
  return _internal_has_txs()
      ? *sum_.txs_
      : reinterpret_cast< ::tendermint::mempool::Txs&>(::tendermint::mempool::_Txs_default_instance_);
}
inline const ::tendermint::mempool::Txs& Message::txs() const {
  // @@protoc_insertion_point(field_get:tendermint.mempool.Message.txs)
  return _internal_txs();
}
inline ::tendermint::mempool::Txs* Message::unsafe_arena_release_txs() {
  // @@protoc_insertion_point(field_unsafe_arena_release:tendermint.mempool.Message.txs)
  if (_internal_has_txs()) {
    clear_has_sum();
    ::tendermint::mempool::Txs* temp = sum_.txs_;
    sum_.txs_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void Message::unsafe_arena_set_allocated_txs(::tendermint::mempool::Txs* txs) {
  clear_sum();
  if (txs) {
    set_has_txs();
    sum_.txs_ = txs;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:tendermint.mempool.Message.txs)
}
inline ::tendermint::mempool::Txs* Message::_internal_mutable_txs() {
  if (!_internal_has_txs()) {
    clear_sum();
    set_has_txs();
    sum_.txs_ = CreateMaybeMessage< ::tendermint::mempool::Txs >(GetArenaForAllocation());
  }
  return sum_.txs_;
}
inline ::tendermint::mempool::Txs* Message::mutable_txs() {
  ::tendermint::mempool::Txs* _msg = _internal_mutable_txs();
  // @@protoc_insertion_point(field_mutable:tendermint.mempool.Message.txs)
  return _msg;
}

inline bool Message::has_sum() const {
  return sum_case() != SUM_NOT_SET;
}
inline void Message::clear_has_sum() {
  _oneof_case_[0] = SUM_NOT_SET;
}
inline Message::SumCase Message::sum_case() const {
  return Message::SumCase(_oneof_case_[0]);
}
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace mempool
}  // namespace tendermint

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_tendermint_2fmempool_2ftypes_2eproto
