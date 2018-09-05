# CAPNPROTO


## install capnproto

```shell
sudo apt install capnproto
```

## install capnproto-c

```shell
git clone https://github.com/opensourcerouting/c-capnproto
cd c-capnproto
git submodule update --init --recursive
autoreconf -f -i -s
./configure
make
make check
sudo make install
```

## basic capnproto protocol

### generating c code

```shell
capnp compile -o c schema.capnp
```

