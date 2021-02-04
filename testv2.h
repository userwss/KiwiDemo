#include "kiwi.h"

namespace testv2 {

#ifndef INCLUDE_TESTV2_H
#define INCLUDE_TESTV2_H

class BinarySchema {
public:
  bool parse(kiwi::ByteBuffer &bb);
  const kiwi::BinarySchema &underlyingSchema() const { return _schema; }
  bool skipTestField(kiwi::ByteBuffer &bb, uint32_t id) const;

private:
  kiwi::BinarySchema _schema;
  uint32_t _indexTest = 0;
};

class Test;

class Test {
public:
  Test() { (void)_flags; }

  int32_t *x();
  const int32_t *x() const;
  void set_x(const int32_t &value);

  int32_t *y();
  const int32_t *y() const;
  void set_y(const int32_t &value);

  bool encode(kiwi::ByteBuffer &bb);
  bool decode(kiwi::ByteBuffer &bb, kiwi::MemoryPool &pool, const BinarySchema *schema = nullptr);

private:
  uint32_t _flags[1] = {};
  int32_t _data_x = {};
  int32_t _data_y = {};
};

#endif
#ifdef IMPLEMENT_SCHEMA_H

bool BinarySchema::parse(kiwi::ByteBuffer &bb) {
  if (!_schema.parse(bb)) return false;
  _schema.findDefinition("Test", _indexTest);
  return true;
}

bool BinarySchema::skipTestField(kiwi::ByteBuffer &bb, uint32_t id) const {
  return _schema.skipField(bb, _indexTest, id);
}

int32_t *Test::x() {
  return _flags[0] & 1 ? &_data_x : nullptr;
}

const int32_t *Test::x() const {
  return _flags[0] & 1 ? &_data_x : nullptr;
}

void Test::set_x(const int32_t &value) {
  _flags[0] |= 1; _data_x = value;
}

int32_t *Test::y() {
  return _flags[0] & 2 ? &_data_y : nullptr;
}

const int32_t *Test::y() const {
  return _flags[0] & 2 ? &_data_y : nullptr;
}

void Test::set_y(const int32_t &value) {
  _flags[0] |= 2; _data_y = value;
}

bool Test::encode(kiwi::ByteBuffer &_bb) {
  if (x() != nullptr) {
    _bb.writeVarUint(1);
    _bb.writeVarInt(_data_x);
  }
  if (y() != nullptr) {
    _bb.writeVarUint(2);
    _bb.writeVarInt(_data_y);
  }
  _bb.writeVarUint(0);
  return true;
}

bool Test::decode(kiwi::ByteBuffer &_bb, kiwi::MemoryPool &_pool, const BinarySchema *_schema) {
  while (true) {
    uint32_t _type;
    if (!_bb.readVarUint(_type)) return false;
    switch (_type) {
      case 0:
        return true;
      case 1: {
        if (!_bb.readVarInt(_data_x)) return false;
        set_x(_data_x);
        break;
      }
      case 2: {
        if (!_bb.readVarInt(_data_y)) return false;
        set_y(_data_y);
        break;
      }
      default: {
        if (!_schema || !_schema->skipTestField(_bb, _type)) return false;
        break;
      }
    }
  }
}

#endif

}
