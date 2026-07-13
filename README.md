Lady who managed to get past the 7-stage hiring process at Bloomberg said she had practiced on Leetcode.

In my experience, some of the problems marked as 'hard' can encourage significant implementation complexity, e.g. #4 requires running two binary searches simultaneously to make it to O(log(n + m)) (even one binary search is a faff to write bug-free).

The 'medium' problems are probably more along the lines of what might occur in a time-based hiring process code challenge, however some tests within may require an algorithm with low computational complexity and to be implemented in a compiled language.

Strategy is to practice prototyping an algorithm quickly (very difficult) in Python, then porting to C quickly (not that hard). LLMs are not yet socially accepted for the latter part, though they are very good at Python to Go ports (relatively similar language features), however Go has many idioms, doesn't receive first-party support in a multi-language context (e.g. have to explicitly make all ints as int32 for tests to work, requiring more idioms). C language features more minimalist, much easier to memorise, hopefully enough for most challenges.
