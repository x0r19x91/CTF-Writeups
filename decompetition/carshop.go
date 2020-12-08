package main

import (
	"fmt"
	"os"
	"strconv"
)

type Color int


func (c Color) String() string {
  var mColors = [...]string{
	"Aurora",
	"Indigo",
	"Charcoal",
	"Jade",
	"Platinum",
}
	return mColors[c]
}

// func (c *Color) String() string {
// 	return mColors[c]
// }

type Car struct {
	// Have fun!
	brand    string
	model    string
	year     int
	odometer int
	color    Color
}

func (c Car) String() string {
	return fmt.Sprintf("{%d %s %s (%s, %d miles)}", c.year, c.brand, c.model, c.color, c.odometer)
}

type CarShop struct {
	// Have fun!
	name      string
	warehouse []Car
	// warehouse []Car
}

func (cs *CarShop) AddCar(brand, model, year, odometer, color string) {
	var cc Car
	nYear, _ := strconv.Atoi(year)
	nOdo, _ := strconv.Atoi(odometer)
	mFuck := make(map[string]Color)
	mFuck["Aurora"] = 0
	mFuck["Indigo"] = 1
	mFuck["Charcoal"] = 2
	mFuck["Jade"] = 3
	mFuck["Platinum"] = 4
	xx := mFuck[color]
	cc = Car{
		brand, model, nYear, nOdo, xx,
	}
	cs.warehouse = append(cs.warehouse, cc)
}

func (cs CarShop) SearchCar(name string) *Car {
	for _, r := range cs.warehouse {
		if name == r.model {
			return &r
		}
	}
	return nil
}

// Have fun!

func main() {
	carShop := CarShop{os.Args[1], make([]Car, 0)}

	for i := 0; i < 3; i++ {
		var brand, model, year, odometer, color string
		fmt.Scanf("%s %s %s %s %s\n", &brand, &model, &year, &odometer, &color)
		carShop.AddCar(brand, model, year, odometer, color)
	}

	fmt.Printf("Welcome to %s's Car Shop!\n", carShop.name)
	fmt.Println("Available Cars:")
	fmt.Printf("%s\n", carShop.warehouse)

	if carShop.SearchCar(os.Args[2]) != nil {
		fmt.Println("This car is available!")
	} else {
		fmt.Println("This car is not available. :-(")
	}
}
