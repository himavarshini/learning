package md5sum

import "fmt"
import "os"
import "io/ioutil"
import "crypto/md5"

func Md5sum(filename string) [16]byte {
    filedata, er := ioutil.ReadFile(filename)
	if er != nil {
	    fmt.Println("failed to open ", filename)
		os.Exit(1)
	}

	hash := md5.Sum(filedata)
	return hash
}

