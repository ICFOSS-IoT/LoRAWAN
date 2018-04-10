function Encoder(object, port) {
  // Encode downlink messages sent as
  // object to an array or buffer of bytes.
  if(object.color == "redon"){
    return[1];
  }
  else if(object.color == "redoff"){
    return [2];
  }
  else if(object.color == "greenon"){
    return [3];
  }
  else if(object.color == "greenoff"){
    return [4];
  }

  // if (port === 1) bytes[0] = object.led ? 1 : 0;

  return [0];
}
