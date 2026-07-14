Lady who managed to get past the 7-stage hiring process at Bloomberg said she had practiced on Leetcode. Note that Bloomberg didn't use automated tests (instead taking an interpersonal approach) last time I tried.

Issues with Leetcode as a source of practice for hiring process code challenges with automated tests:
- Some Leetcode tests cover cumbersome edge cases (typically there are 100s or 1000s of tests, but only ~20 in a hiring challenge), that may be of no interest to interviewers
- Some Leetcode challenges may require niche prerequisite computer science knowledge, however these types of challenges may be more along the lines of Project Euler
- Some Leetcode challenges may have average implementation times far longer than a typical hiring process code challenge time limit (e.g. Leetcode #4 which suggests implementing two binary searches that run in parallel, and then converge, to get to O(log(m + n))

Similarities:
- As Leetcode tests per challenge are in the quantity of 100s and 1000s, typically not all are read through to complete a challenge; similar to 'hidden' tests in a hiring process challenge (i.e. test input and output is not provided to developer)
- In both Leetcode and hiring process challenges, typically time limits are provided implicitly, and so the developer is expected to eyeball an algorithm that will fit within them (arguably unreasonable)
- Leetcode provides acceptance scores (how many people passed all provided tests), which are sometimes out-of-sync with difficulty labels, and hiring process challenges are typically looking primarily at acceptance scores
- Developers can fall victim to thinking of solutions from the perspective of known, formally recognised algorithms, rather than inventing new, more efficient ones based on the context
- Browser based interfaces, play buttons and all...

Strategy is to practice prototyping an algorithm quickly (very difficult) in Python, then porting to C quickly (not that hard). LLMs are not yet socially accepted for the latter part, though they are very good at Python to Go ports (relatively similar language features), however Go has many idioms, doesn't receive first-party support in a multi-language context (e.g. have to explicitly make all ints as int32 for tests to work, requiring more idioms). C language features more minimalist, much easier to memorise, hopefully enough for most challenges.

Algorithm design can be an exploratory process, based on experiments and observations, so, how to speed this up? Speed up ability to prototype?
