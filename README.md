Lady who managed to get past the 7-stage hiring process at Bloomberg said she had practiced on Leetcode. Note that Bloomberg didn't use automated tests (instead taking an interpersonal approach) last time I tried.

Issues with Leetcode as a source of practice for hiring process code challenges with automated tests:
- Some Leetcode tests cover rare edge cases (typically there are 100s or 1000s of tests, but only ~20 in a hiring challenge),
- Some Leetcode challenges may require niche pre-requisite computer science knowledge, but hiring process challenges may seek to present a problem that is relatively new to all, to test the ability to design new algorithms (as opposed to implementing known algorithms)
- Some Leetcode challenges may have average implementation times far longer than a typical hiring process code challenge time limit (e.g. Leetcode #4 which requires implementing two binary searches that run in parallel, and then converge, to get to O(log(m + n))

The 'medium' problems are probably more along the lines of what might occur in a time-based hiring process code challenge.

Strategy is to practice prototyping an algorithm quickly (very difficult) in Python, then porting to C quickly (not that hard). LLMs are not yet socially accepted for the latter part, though they are very good at Python to Go ports (relatively similar language features), however Go has many idioms, doesn't receive first-party support in a multi-language context (e.g. have to explicitly make all ints as int32 for tests to work, requiring more idioms). C language features more minimalist, much easier to memorise, hopefully enough for most challenges.

Algorithm design can be an exploratory process, based on experiments and observations, so, how to speed this up? Speed up ability to prototype?
