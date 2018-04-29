package main

import "fmt"
import "os"
import "net"

func main() {
	interfaces, err := net.Interfaces()
	if err != nil {
		fmt.Println("failed to get interface list\n")
		os.Exit(1)
	}

	//fmt.Println(interfaces)

	for i := 0; i < len(interfaces); i++ {
		fmt.Print("Ifname: " + interfaces[i].Name + "\t");

		fmt.Print("Ifindex: ")
		fmt.Print(interfaces[i].Index);
		fmt.Print("\t")

		fmt.Print("HWAddr: ");
		fmt.Print(interfaces[i].HardwareAddr);
		fmt.Print("\t");

		fmt.Print("MTU: ");
		fmt.Print(interfaces[i].MTU);

		fmt.Println();
	}
}

