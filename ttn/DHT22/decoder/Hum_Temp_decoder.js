function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};
  decoded.temp = ((bytes[0] << 8)+ bytes[1])/100;
  decoded.hum = ((bytes[2] << 8)+ bytes[3])/100;
  return decoded;
}
