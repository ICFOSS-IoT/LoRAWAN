function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};
  decoded.hum = (bytes[0] << 8)+ bytes[1];
  decoded.temp = (bytes[2] << 8)+ bytes[3];
  return decoded;
}
