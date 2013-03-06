/***************************************************************************************************
 *  Copyright 2012 maidsafe.net limited                                                            *
 *                                                                                                 *
 *  The following source code is property of MaidSafe.net limited and is not meant for external    *
 *  use. The use of this code is governed by the licence file licence.txt found in the root of     *
 *  this directory and also on www.maidsafe.net.                                                   *
 *                                                                                                 *
 *  You are not free to copy, amend or otherwise use this source code without the explicit written *
 *  permission of the board of directors of MaidSafe.net.                                          *
 **************************************************************************************************/

#include "maidsafe/passport/detail/public_fob.h"

#include "maidsafe/common/utils.h"

#include "maidsafe/passport/detail/passport_pb.h"


namespace maidsafe {

namespace passport {

namespace detail {

void PublicFobFromProtobuf(const NonEmptyString& serialised_public_fob,
                           DataTagValue enum_value,
                           asymm::PublicKey& public_key,
                           asymm::Signature& validation_token) {
  protobuf::PublicFob proto_public_fob;
  if (!proto_public_fob.ParseFromString(serialised_public_fob.string()))
    ThrowError(PassportErrors::fob_parsing_error);
  validation_token = asymm::Signature(proto_public_fob.validation_token());
  public_key = asymm::DecodeKey(asymm::EncodedPublicKey(proto_public_fob.encoded_public_key()));
  if (static_cast<int>(enum_value) != proto_public_fob.type())
    ThrowError(PassportErrors::fob_parsing_error);
}

NonEmptyString PublicFobToProtobuf(DataTagValue enum_value,
                                   const asymm::PublicKey& public_key,
                                   const asymm::Signature& validation_token) {
  protobuf::PublicFob proto_public_fob;
  proto_public_fob.set_type(static_cast<int>(enum_value));
  proto_public_fob.set_encoded_public_key(asymm::EncodeKey(public_key).string());
  proto_public_fob.set_validation_token(validation_token.string());
  return NonEmptyString(proto_public_fob.SerializeAsString());
}

}  // namespace detail

}  // namespace passport

}  // namespace maidsafe