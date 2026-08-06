package main

import (
	"strings"
)

//  The following is an automated port from the Python version, 3900_longest_balanced_substring.py, via Gemini 3.6 Flash LLM.
//  Only 2 lines were changed, in very small ways, in calculateCounts(), and comments added.

//  955/992 test pass, failure due to execution timeout,
//    i.e. worse performance than the Python version (but not much in it).


type counts map[byte]int

func copyCounts(c counts) counts {
	newC := make(counts, len(c))
	for k, v := range c {
		newC[k] = v
	}
	return newC
}

// orderedMap string -> counts
type orderedCountsMap struct {
	m    map[string]counts
	keys []string
}

func newOrderedCountsMap() *orderedCountsMap {
	return &orderedCountsMap{
		m:    make(map[string]counts),
		keys: make([]string, 0),
	}
}

func (o *orderedCountsMap) get(key string) (counts, bool) {
	val, ok := o.m[key]
	return val, ok
}

func (o *orderedCountsMap) set(key string, val counts) {
	if _, exists := o.m[key]; !exists {
		o.keys = append(o.keys, key)
	}
	o.m[key] = val
}

func (o *orderedCountsMap) popFirst() {
	if len(o.keys) == 0 {
		return
	}
	firstKey := o.keys[0]
	o.keys = o.keys[1:]
	delete(o.m, firstKey)
}

// orderedMap string -> int
type orderedIntMap struct {
	m    map[string]int
	keys []string
}

func newOrderedIntMap() *orderedIntMap {
	return &orderedIntMap{
		m:    make(map[string]int),
		keys: make([]string, 0),
	}
}

func (o *orderedIntMap) get(key string) (int, bool) {
	val, ok := o.m[key]
	return val, ok
}

func (o *orderedIntMap) set(key string, val int) {
	if _, exists := o.m[key]; !exists {
		o.keys = append(o.keys, key)
	}
	o.m[key] = val
}

func (o *orderedIntMap) popFirst() {
	if len(o.keys) == 0 {
		return
	}
	firstKey := o.keys[0]
	o.keys = o.keys[1:]
	delete(o.m, firstKey)
}

func hsh(s string) string {
	return s
}

func makeCounter(s string) counts {
	c := counts{'0': 0, '1': 0}
	for i := 0; i < len(s); i++ {
		c[s[i]]++
	}
	return c
}

func checkString(s, subS string, c counts, pos int) int {
	var target byte = 0

	if c['0'] == c['1'] {
		return len(subS)
	} else if c['0']-1 == c['1']+1 {
		target = '1'
	} else if c['0']+1 == c['1']-1 {
		target = '0'
	}

	if target != 0 {
		preStr := s[:pos]
		postStr := s[pos+len(subS):]

		if strings.IndexByte(preStr, target) != -1 || strings.IndexByte(postStr, target) != -1 {
			return len(subS)
		}
	}

	return -1
}

func calculateCounts(s, subS string, ssCounts *orderedCountsMap, runningCounter counts, i, q int) (counts, *orderedCountsMap) {
	toPrepend := ""
	toAppend := ""

  //  FOLLOWING LINE MANUALLY EDITED FROM AUTOMATED PORT.
	if i > 1 {
		toPrepend = s[i-2 : i]
	}
	if toPrepend == "" {
		toPrepend = "__"
	}

  //  FOLLOWING LINE MANUALLY EDITED FROM AUTOMATED PORT.
	if i+q+2 <= len(s) {
		toAppend = s[i+q : i+q+2]
	}
	if toAppend == "" {
		toAppend = "__"
	}

	extraChars := [2]string{toPrepend, toAppend}

	if runningCounter['0'] == 0 && runningCounter['1'] == 0 {
		key1 := hsh(extraChars[0] + subS)
		key2 := hsh(subS + extraChars[1])

		if val, exists := ssCounts.get(key1); exists {
			runningCounter = copyCounts(val)
			runningCounter[extraChars[0][0]]--
			runningCounter[extraChars[0][1]]--
		} else if val, exists := ssCounts.get(key2); exists {
			runningCounter = copyCounts(val)
			runningCounter[extraChars[1][0]]--
			runningCounter[extraChars[1][1]]--
		} else {
			ssCounts.set(hsh(subS), makeCounter(subS))
		}
	} else {
		runningCounter[s[i-1]]--
		runningCounter[subS[len(subS)-1]]++
	}

	ssCounts.set(hsh(subS), copyCounts(runningCounter))
	return runningCounter, ssCounts
}

func longestBalanced(s string) int {
	if !strings.Contains(s, "1") || !strings.Contains(s, "0") {
		return 0
	}

	balStringChks := newOrderedIntMap()
	ssCounts := newOrderedCountsMap()
	biggestStr := true

	initQ := len(s)
	if initQ%2 != 0 {
		initQ = len(s) - 1
	}

	wQuantity := [2]int{0, 0}
	wQuantityBatch := 0

	for q := initQ; q > 0; q -= 2 {
		wQuantity = [2]int{wQuantityBatch, wQuantity[0]}
		wQuantityBatch = 0

		for wQuantity[1] > 0 {
			ssCounts.popFirst()
			balStringChks.popFirst()
			wQuantity[1]--
		}

		runningCounter := counts{'0': 0, '1': 0}

		for i := 0; i < len(s); i++ {
			if i+q > len(s) {
				break
			}

			subS := s[i : i+q]

			if biggestStr {
				biggestStr = false
				cnts := makeCounter(subS)
				rc := copyCounts(runningCounter)
				for k, v := range cnts {
					rc[k] = v
				}
				ssCounts.set(hsh(subS), rc)
			}

			if _, exists := ssCounts.get(hsh(subS)); !exists {
				runningCounter, ssCounts = calculateCounts(s, subS, ssCounts, copyCounts(runningCounter), i, q)
				wQuantityBatch++
			} else {
				val, _ := ssCounts.get(hsh(subS))
				runningCounter = copyCounts(val)
			}

			if _, exists := balStringChks.get(subS); !exists {
				cntVal, _ := ssCounts.get(hsh(subS))
				balStringChks.set(hsh(subS), checkString(s, subS, cntVal, i))
			}

			if res, _ := balStringChks.get(hsh(subS)); res > -1 {
				return res
			}
		}
	}

	return 0
}
