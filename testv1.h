#include "kiwi.h"

class BinarySchema {
public:
  bool parse(kiwi::ByteBuffer &bb);
  const kiwi::BinarySchema &underlyingSchema() const { return _schema; }
  bool skipExampleField(kiwi::ByteBuffer &bb, uint32_t id) const;

private:
  kiwi::BinarySchema _schema;
  uint32_t _indexExample = 0;
};

enum class Type : uint32_t {
  FLAT = 0,
  ROUND = 1,
  POINTED = 2,
};

class Color;
class Example;

class Color {
public:
  Color() { (void)_flags; }

  int32_t *red();
  const int32_t *red() const;
  void set_red(const int32_t &value);

  int32_t *green();
  const int32_t *green() const;
  void set_green(const int32_t &value);

  int32_t *blue();
  const int32_t *blue() const;
  void set_blue(const int32_t &value);

  int32_t *alpha();
  const int32_t *alpha() const;
  void set_alpha(const int32_t &value);

  bool encode(kiwi::ByteBuffer &bb);
  bool decode(kiwi::ByteBuffer &bb, kiwi::MemoryPool &pool, const BinarySchema *schema = nullptr);

private:
  uint32_t _flags[1] = {};
  int32_t _data_red = {};
  int32_t _data_green = {};
  int32_t _data_blue = {};
  int32_t _data_alpha = {};
};

class Example {
public:
  Example() { (void)_flags; }

  float *clientID();
  const float *clientID() const;
  void set_clientID(const float &value);

  Type *type();
  const Type *type() const;
  void set_type(const Type &value);

  kiwi::Array<Color> *colors();
  const kiwi::Array<Color> *colors() const;
  kiwi::Array<Color> &set_colors(kiwi::MemoryPool &pool, uint32_t count);

  kiwi::String *str();
  const kiwi::String *str() const;
  void set_str(const kiwi::String &value);

  bool encode(kiwi::ByteBuffer &bb);
  bool decode(kiwi::ByteBuffer &bb, kiwi::MemoryPool &pool, const BinarySchema *schema = nullptr);

private:
  uint32_t _flags[1] = {};
  Type _data_type = {};
  kiwi::Array<Color> _data_colors = {};
  kiwi::String _data_str = {};
  float _data_clientID = {};
};

#ifdef IMPLEMENT_SCHEMA_H

bool BinarySchema::parse(kiwi::ByteBuffer &bb) {
  if (!_schema.parse(bb)) return false;
  _schema.findDefinition("Example", _indexExample);
  return true;
}

bool BinarySchema::skipExampleField(kiwi::ByteBuffer &bb, uint32_t id) const {
  return _schema.skipField(bb, _indexExample, id);
}

int32_t *Color::red() {
  return _flags[0] & 1 ? &_data_red : nullptr;
}

const int32_t *Color::red() const {
  return _flags[0] & 1 ? &_data_red : nullptr;
}

void Color::set_red(const int32_t &value) {
  _flags[0] |= 1; _data_red = value;
}

int32_t *Color::green() {
  return _flags[0] & 2 ? &_data_green : nullptr;
}

const int32_t *Color::green() const {
  return _flags[0] & 2 ? &_data_green : nullptr;
}

void Color::set_green(const int32_t &value) {
  _flags[0] |= 2; _data_green = value;
}

int32_t *Color::blue() {
  return _flags[0] & 4 ? &_data_blue : nullptr;
}

const int32_t *Color::blue() const {
  return _flags[0] & 4 ? &_data_blue : nullptr;
}

void Color::set_blue(const int32_t &value) {
  _flags[0] |= 4; _data_blue = value;
}

int32_t *Color::alpha() {
  return _flags[0] & 8 ? &_data_alpha : nullptr;
}

const int32_t *Color::alpha() const {
  return _flags[0] & 8 ? &_data_alpha : nullptr;
}

void Color::set_alpha(const int32_t &value) {
  _flags[0] |= 8; _data_alpha = value;
}

bool Color::encode(kiwi::ByteBuffer &_bb) {
  if (red() == nullptr) return false;
  _bb.writeVarInt(_data_red);
  if (green() == nullptr) return false;
  _bb.writeVarInt(_data_green);
  if (blue() == nullptr) return false;
  _bb.writeVarInt(_data_blue);
  if (alpha() == nullptr) return false;
  _bb.writeVarInt(_data_alpha);
  return true;
}

bool Color::decode(kiwi::ByteBuffer &_bb, kiwi::MemoryPool &_pool, const BinarySchema *_schema) {
  if (!_bb.readVarInt(_data_red)) return false;
  set_red(_data_red);
  if (!_bb.readVarInt(_data_green)) return false;
  set_green(_data_green);
  if (!_bb.readVarInt(_data_blue)) return false;
  set_blue(_data_blue);
  if (!_bb.readVarInt(_data_alpha)) return false;
  set_alpha(_data_alpha);
  return true;
}

float *Example::clientID() {
  return _flags[0] & 1 ? &_data_clientID : nullptr;
}

const float *Example::clientID() const {
  return _flags[0] & 1 ? &_data_clientID : nullptr;
}

void Example::set_clientID(const float &value) {
  _flags[0] |= 1; _data_clientID = value;
}

Type *Example::type() {
  return _flags[0] & 2 ? &_data_type : nullptr;
}

const Type *Example::type() const {
  return _flags[0] & 2 ? &_data_type : nullptr;
}

void Example::set_type(const Type &value) {
  _flags[0] |= 2; _data_type = value;
}

kiwi::Array<Color> *Example::colors() {
  return _flags[0] & 4 ? &_data_colors : nullptr;
}

const kiwi::Array<Color> *Example::colors() const {
  return _flags[0] & 4 ? &_data_colors : nullptr;
}

kiwi::Array<Color> &Example::set_colors(kiwi::MemoryPool &pool, uint32_t count) {
  _flags[0] |= 4; return _data_colors = pool.array<Color>(count);
}

kiwi::String *Example::str() {
  return _flags[0] & 8 ? &_data_str : nullptr;
}

const kiwi::String *Example::str() const {
  return _flags[0] & 8 ? &_data_str : nullptr;
}

void Example::set_str(const kiwi::String &value) {
  _flags[0] |= 8; _data_str = value;
}

bool Example::encode(kiwi::ByteBuffer &_bb) {
  if (clientID() != nullptr) {
    _bb.writeVarUint(1);
    _bb.writeVarFloat(_data_clientID);
  }
  if (type() != nullptr) {
    _bb.writeVarUint(2);
    _bb.writeVarUint(static_cast<uint32_t>(_data_type));
  }
  if (colors() != nullptr) {
    _bb.writeVarUint(3);
    _bb.writeVarUint(_data_colors.size());
    for (Color &_it : _data_colors) if (!_it.encode(_bb)) return false;
  }
  if (str() != nullptr) {
    _bb.writeVarUint(4);
    _bb.writeString(_data_str.c_str());
  }
  _bb.writeVarUint(0);
  return true;
}

bool Example::decode(kiwi::ByteBuffer &_bb, kiwi::MemoryPool &_pool, const BinarySchema *_schema) {
  uint32_t _count;
  while (true) {
    uint32_t _type;
    if (!_bb.readVarUint(_type)) return false;
    switch (_type) {
      case 0:
        return true;
      case 1: {
        if (!_bb.readVarFloat(_data_clientID)) return false;
        set_clientID(_data_clientID);
        break;
      }
      case 2: {
        if (!_bb.readVarUint(reinterpret_cast<uint32_t &>(_data_type))) return false;
        set_type(_data_type);
        break;
      }
      case 3: {
        if (!_bb.readVarUint(_count)) return false;
        for (Color &_it : set_colors(_pool, _count)) if (!_it.decode(_bb, _pool, _schema)) return false;
        break;
      }
      case 4: {
        if (!_bb.readString(_data_str, _pool)) return false;
        set_str(_data_str);
        break;
      }
      default: {
        if (!_schema || !_schema->skipExampleField(_bb, _type)) return false;
        break;
      }
    }
  }
}

#endif
