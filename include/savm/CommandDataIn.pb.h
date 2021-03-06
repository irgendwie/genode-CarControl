// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommandDataIn.proto

#ifndef PROTOBUF_CommandDataIn_2eproto__INCLUDED
#define PROTOBUF_CommandDataIn_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_CommandDataIn_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsCommandDataInImpl();
void InitDefaultsCommandDataIn();
inline void InitDefaults() {
  InitDefaultsCommandDataIn();
}
}  // namespace protobuf_CommandDataIn_2eproto
namespace protobuf {
class CommandDataIn;
class CommandDataInDefaultTypeInternal;
extern CommandDataInDefaultTypeInternal _CommandDataIn_default_instance_;
}  // namespace protobuf
namespace protobuf {

// ===================================================================

class CommandDataIn : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:protobuf.CommandDataIn) */ {
 public:
  CommandDataIn();
  virtual ~CommandDataIn();

  CommandDataIn(const CommandDataIn& from);

  inline CommandDataIn& operator=(const CommandDataIn& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CommandDataIn(CommandDataIn&& from) noexcept
    : CommandDataIn() {
    *this = ::std::move(from);
  }

  inline CommandDataIn& operator=(CommandDataIn&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CommandDataIn& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CommandDataIn* internal_default_instance() {
    return reinterpret_cast<const CommandDataIn*>(
               &_CommandDataIn_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(CommandDataIn* other);
  friend void swap(CommandDataIn& a, CommandDataIn& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CommandDataIn* New() const PROTOBUF_FINAL { return New(NULL); }

  CommandDataIn* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CommandDataIn& from);
  void MergeFrom(const CommandDataIn& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(CommandDataIn* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // float steer = 1;
  void clear_steer();
  static const int kSteerFieldNumber = 1;
  float steer() const;
  void set_steer(float value);

  // float accel = 2;
  void clear_accel();
  static const int kAccelFieldNumber = 2;
  float accel() const;
  void set_accel(float value);

  // float brakeFL = 3;
  void clear_brakefl();
  static const int kBrakeFLFieldNumber = 3;
  float brakefl() const;
  void set_brakefl(float value);

  // float brakeFR = 4;
  void clear_brakefr();
  static const int kBrakeFRFieldNumber = 4;
  float brakefr() const;
  void set_brakefr(float value);

  // float brakeRL = 5;
  void clear_brakerl();
  static const int kBrakeRLFieldNumber = 5;
  float brakerl() const;
  void set_brakerl(float value);

  // float brakeRR = 6;
  void clear_brakerr();
  static const int kBrakeRRFieldNumber = 6;
  float brakerr() const;
  void set_brakerr(float value);

  // int32 gear = 7;
  void clear_gear();
  static const int kGearFieldNumber = 7;
  ::google::protobuf::int32 gear() const;
  void set_gear(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:protobuf.CommandDataIn)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  float steer_;
  float accel_;
  float brakefl_;
  float brakefr_;
  float brakerl_;
  float brakerr_;
  ::google::protobuf::int32 gear_;
  mutable int _cached_size_;
  friend struct ::protobuf_CommandDataIn_2eproto::TableStruct;
  friend void ::protobuf_CommandDataIn_2eproto::InitDefaultsCommandDataInImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CommandDataIn

// float steer = 1;
inline void CommandDataIn::clear_steer() {
  steer_ = 0;
}
inline float CommandDataIn::steer() const {
  // @@protoc_insertion_point(field_get:protobuf.CommandDataIn.steer)
  return steer_;
}
inline void CommandDataIn::set_steer(float value) {
  
  steer_ = value;
  // @@protoc_insertion_point(field_set:protobuf.CommandDataIn.steer)
}

// float accel = 2;
inline void CommandDataIn::clear_accel() {
  accel_ = 0;
}
inline float CommandDataIn::accel() const {
  // @@protoc_insertion_point(field_get:protobuf.CommandDataIn.accel)
  return accel_;
}
inline void CommandDataIn::set_accel(float value) {
  
  accel_ = value;
  // @@protoc_insertion_point(field_set:protobuf.CommandDataIn.accel)
}

// float brakeFL = 3;
inline void CommandDataIn::clear_brakefl() {
  brakefl_ = 0;
}
inline float CommandDataIn::brakefl() const {
  // @@protoc_insertion_point(field_get:protobuf.CommandDataIn.brakeFL)
  return brakefl_;
}
inline void CommandDataIn::set_brakefl(float value) {
  
  brakefl_ = value;
  // @@protoc_insertion_point(field_set:protobuf.CommandDataIn.brakeFL)
}

// float brakeFR = 4;
inline void CommandDataIn::clear_brakefr() {
  brakefr_ = 0;
}
inline float CommandDataIn::brakefr() const {
  // @@protoc_insertion_point(field_get:protobuf.CommandDataIn.brakeFR)
  return brakefr_;
}
inline void CommandDataIn::set_brakefr(float value) {
  
  brakefr_ = value;
  // @@protoc_insertion_point(field_set:protobuf.CommandDataIn.brakeFR)
}

// float brakeRL = 5;
inline void CommandDataIn::clear_brakerl() {
  brakerl_ = 0;
}
inline float CommandDataIn::brakerl() const {
  // @@protoc_insertion_point(field_get:protobuf.CommandDataIn.brakeRL)
  return brakerl_;
}
inline void CommandDataIn::set_brakerl(float value) {
  
  brakerl_ = value;
  // @@protoc_insertion_point(field_set:protobuf.CommandDataIn.brakeRL)
}

// float brakeRR = 6;
inline void CommandDataIn::clear_brakerr() {
  brakerr_ = 0;
}
inline float CommandDataIn::brakerr() const {
  // @@protoc_insertion_point(field_get:protobuf.CommandDataIn.brakeRR)
  return brakerr_;
}
inline void CommandDataIn::set_brakerr(float value) {
  
  brakerr_ = value;
  // @@protoc_insertion_point(field_set:protobuf.CommandDataIn.brakeRR)
}

// int32 gear = 7;
inline void CommandDataIn::clear_gear() {
  gear_ = 0;
}
inline ::google::protobuf::int32 CommandDataIn::gear() const {
  // @@protoc_insertion_point(field_get:protobuf.CommandDataIn.gear)
  return gear_;
}
inline void CommandDataIn::set_gear(::google::protobuf::int32 value) {
  
  gear_ = value;
  // @@protoc_insertion_point(field_set:protobuf.CommandDataIn.gear)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CommandDataIn_2eproto__INCLUDED
