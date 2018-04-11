package main

import (
	"fmt"
	"regexp"
	"bytes"
)

/**
 * Find(All)?(String)?(Submatch)?(Index)?
 */

func main(){
	oozing := "Hi, Aario Ai!"
	match, _ := regexp.MatchString("[aA]", oozing)	// true


	r, _:= regexp.Compile("[aA]+r?io?")

	m := r.Match([]byte(oozing));							// true
	ms := r.MatchString(oozing)								// true
	fs := r.FindString(oozing) 								// Aario
	fsi := r.FindStringIndex(oozing)						// [4 9]
	fss := r.FindStringSubmatch(oozing)						// [Aario],  如果有子项，那么会同时匹配子项
	fssi := r.FindStringSubmatchIndex(oozing)				// [4 9]
	fas := r.FindAllString(oozing, -1)					// [Aario Ai]
	fass := r.FindAllStringSubmatch(oozing, -1)			// [[Aario] [Ai]]
	fassi := r.FindAllStringSubmatchIndex(oozing, -1)		// [[4 9] [10 12]]

	ras := r.ReplaceAllString(oozing, "<messy>")		// Hi, <messy> <messy>!
	raf := r.ReplaceAllFunc([]byte(oozing), bytes.ToUpper)	// [72 105 44 32 65 65 82 73 79 32 65 73 33]

	fmt.Println(match, m, ms, fs, fsi, fss, fssi, fas, fass, fassi, ras, raf)

	resembles := "http://luexu.com/o-o/100.png"
	r2, _:= regexp.Compile("https?://(.*)/o-o/(.*)")

	fss2 := r2.FindStringSubmatch(resembles)					// [http://luexu.com/o-o/100.png luexu.com 100.png]
	fssi2 := r2.FindStringSubmatchIndex(resembles)				// [0 28 7 16 21 28]
	fas2 := r2.FindAllString(resembles, -1)					// [http://luexu.com/o-o/100.png]
	fass2 := r2.FindAllStringSubmatch(resembles, -1)			// [[http://luexu.com/o-o/100.png luexu.com 100.png]]
	fassi2 := r2.FindAllStringSubmatchIndex(resembles, -1)	// [[0 28 7 16 21 28]]
	fmt.Println(fss2, fssi2, fas2, fass2, fassi2)
	fmt.Println(fss2[1])										// luexu.com

}