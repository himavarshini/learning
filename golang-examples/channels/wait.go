package main

import "fmt"
import "time"

func work_msg(done chan bool) {

	for {
		msg_complete := <-done
		if msg_complete == true {
			fmt.Println("stopping the program received signal")
			break
		} else {
			fmt.Println("Programming running ")
		}
	}
}

func main() {
	done := make(chan bool, 1)
	done <- false
	go work_msg(done)
	time.Sleep(time.Second)
	done <- true
	time.Sleep(time.Second)
}

