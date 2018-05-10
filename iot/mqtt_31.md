
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



### some learnt concepts:

1. both the client and server can send PUBLISH messages.

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
	struct mqtt_fixed
}
```
