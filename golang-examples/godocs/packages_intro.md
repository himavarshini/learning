Packages are kinda libs in C language.

Setup:

1 . set the GOPATH variable in your command line.

   do it in ~/.bash_profile or ~/.bashrc 

example:

```bash
GOPATH="$HOME"
export GOPATH
```

2 . create a directory called src/package_name. Where package_name is your package name.

example:

```bash
mkdir -p $GOPATH/src/even
```
3 . build and install your package

example:

```bash
cd $(GOPATH)/src/even
go build
go install
```

4 . You are ready and start using your package in your app.
