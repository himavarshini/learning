
# MQTT protocol

## very important references:

1. https://www.hivemq.com/blog/mqtt-essentials-part2-publish-subscribe

## overview

1. follow publish/subscriber formats. unlike the client/server model where client directly communicates with the server.
2. in mqtt the end point publish data to the server (alos called broker) and the other clients register to the broker by subscribe model. when the message comes from the end-point client, the message is then copied to each client nodes that subscribed.
3. near-realtime delivery of the messages

### broker
1 broker is the in-between guy between the clients and end-points.
2. broker allows concurrent connections happen. filters the message and delivers to all subscribe clients.
3. broker maintains all the client connections and missed messages - also manages authentication and authorization of clients
4. MQTT is based on top of tcp/ip stack and both client and server needs to have the tcp/ip stack

### message sequencing

1. client sends a CONNECT request <-> broker sends a CONNACK response to client. as long as the 

### message filtering:

#### 1. subject based filtering:

1. each end-point can send out a message on a particular subject. The receiving client subscribes on the topics it is interesetd in with the broker.


## formats

### 1. CONNECT command

1. client to server for initiate the connection, if it sent more than once or delays, the server / broker will close this connection.

```c

struct mqtt_connect_flags {
    uint8_t username:1;
    uint8_t pw:1;
    uint8_t will_retain:1;
    uint8_t will_qos:2;
    uint8_t will:1;
    uint8_t clean_sess:1;
    uint8_t reserved:1;
};

struct mqtt_connect_var_hdr {
    uint8_t protoname[6];
    uint8_t protolvl; // 4 is default
    struct mqtt_connect_flags conn_flags;
};

struct mqtt_connect_fixed_hdr {
    uint8_t mqtt_fixed_header:4;
    uint8_t reserved:4;
    uint8_t remaining_length;
};

struct mqtt_connect_hdr {
    struct mqtt_connect_fixed_hdr fixed_hdr;
    struct mqtt_connect_var_hdr var_hdr;
};
```

1. if protoname is not 'MQTT' the server will disconnect the client.
2. if protolevel is not 4, then the server must respond to the CONNECT packet with CONNACK return code 0x01 and disconnect client.

## fixed header: byte 1:

### message types:

```c
enum message_type {
    RESERVED = 0,
    CONNECT,
    CONNACK,
    PUBLISH,
    PUBACK,
    PUBREC,
    PUBREL,
    PUBCOMP,
    SUBSCRIBE,
    SUBACK,
    UNSUBSCRIBE,
    UNSUBACK,
    PINGREQ,
    PINGRESP,
    DISCONNECT,
    RESERVED = 15,	
};
```


### dup:

1. set to 1 if clients tries to redeliver a PUBLISH, PUBREL, SUBSCRIBE or UNSUBSCRIBE message.
2. applies to only messages with QOS > 0.
3. ACK is required.
4. if dup is set, then the variable header reuqires a messaeg id

using dup, the receipient shall identify if this message has been received before.

### qos:

1. indicate the level of assurance delivery of a `PUBLISH` message.
2. when a client sent a PUBLISH to the server, if the RETAIN flag is set to 1, the server should hold on to the message after it has been delivered to the current subscribers.
3. when a new subscriber is established on the topic, the last retained message on that topic should be sent to the subscribers with the retain flag is set. if there is no retained message, nothing is sent.
4. retained messages should be kept over restarts of the server
5. server may delete a retained message, if it receives a message with a zero-length payload and the retain flag set on the same topic


```c
enum qos {
    FIRE_AND_FORGET =0,
    ACKED_DELIVERY,
    ASSURED_DELIVERY,
    RESERVED =3,
};
```

## fixed header: byte 2:

### remaining length:

1. remaining length avaialble with in current message, including data in the variable header and the payload.

Encoding the digit:

```c
do
    digit = x % 128;
    x = x / 128;
    // if there are more digits to encode, set the top bits of this digit
    if (x > 0)
        digit = digit | 0x80;
while (x > 0);
```

Decoding the digit:

```c
multiplier = 1
value = 0
do
    digit = get_next_digit_from_stream();
    value += (digit & 0x7F) * multiplier
    multiplier *= 0x80;
while ((digit & 0x80) != 0);
```

value contains the remaining length in bits.


## variable header:

### protocol name

1. present in the MQTT CONNECT message.
2. current protocol version value is 3

```c
uint8 protocol_version
```

## messages:


### some learnt concepts:

1. both the client and server can send PUBLISH messages.

## MQTT C structures

```c
struct mqtt_fixed_hdr_byte_1 {
	uint8_t message_type:4;
	uint8_t dup_flag:1;
	uint8_t qos_level:2;
	uint8_t retain:1;
} __attribute__ ((__packed__));

struct mqtt_fixed_hdr_byte_2 {
	uint8_t remaining_len;
} __attribute__ ((__packed__));

struct mqtt_fixed_hdr {
	struct mqtt_fixed_hdr_byte_1 byte1;
	struct mqtt_fixed_hdr_byte_2 byte2;
}
```
