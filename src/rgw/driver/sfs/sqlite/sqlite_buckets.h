// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t
// vim: ts=8 sw=2 smarttab ft=cpp
/*
 * Ceph - scalable distributed file system
 * SFS SAL implementation
 *
 * Copyright (C) 2022 SUSE LLC
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation. See file COPYING.
 */
#pragma once

#include "buckets/bucket_conversions.h"
#include "dbconn.h"

namespace rgw::sal::sfs::sqlite {

class SQLiteBuckets {
  DBConnRef conn;

 public:
  explicit SQLiteBuckets(DBConnRef _conn);
  virtual ~SQLiteBuckets() = default;

  SQLiteBuckets(const SQLiteBuckets&) = delete;
  SQLiteBuckets& operator=(const SQLiteBuckets&) = delete;

  std::optional<DBOPBucketInfo> get_bucket(const std::string& bucket_id) const;
  std::vector<DBOPBucketInfo> get_bucket_by_name(const std::string& bucket_name
  ) const;
  /// get_onwer returns bucket ownership information as a pair of
  /// (user id, display name) or nullopt
  std::optional<std::pair<std::string, std::string>> get_owner(
      const std::string& bucket_id
  ) const;

  void store_bucket(const DBOPBucketInfo& bucket) const;
  void remove_bucket(const std::string& bucket_id) const;

  std::vector<std::string> get_bucket_ids() const;
  std::vector<std::string> get_bucket_ids(const std::string& user_id) const;

  std::vector<DBOPBucketInfo> get_buckets() const;
  std::vector<DBOPBucketInfo> get_buckets(const std::string& user_id) const;

  std::vector<std::string> get_deleted_buckets_ids() const;

  bool bucket_empty(const std::string& bucket_id) const;
  std::optional<DBDeletedObjectItems> delete_bucket_transact(
      const std::string& bucket_id, uint max_objects, bool& bucket_deleted
  ) const;
};

}  // namespace rgw::sal::sfs::sqlite
