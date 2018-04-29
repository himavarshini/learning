package main

import "encoding/csv"
import "fmt"
import "os"
import "io"

func main() {
    file, er := os.Open("sample.csv")
	if er != nil {
	    fmt.Println("file open error")
		return
	}

	defer file.Close()

	reader := csv.NewReader(file)

	reader.Comma = ','

	for {
	    record, er := reader.Read()
		if er == io.EOF {
		    break
		} else if er != nil {
		    fmt.Println("file read error")
			return
		}

		for i := 0; i < len(record); i++ {
		    fmt.Println(" ", record[i])
		}
		fmt.Println()
	}
}

