# RLE & Dictionary Coding Compression Benchmark in C++

## How to Compile & Run

```bash
make build && make run
```

## Background

Data compression is the process of reducing the size of data by encoding it in a way that reduces the amount of space it takes up. There are many different compression algorithms, each with its own strengths and weaknesses. Two of the most common compression algorithms are RLE (Run Length Encoding) and Dictionary Coding.

### RLE (Run Length Encoding)

RLE is a simple form of data compression in which runs of data are stored as a single data value and count. It is a lossless compression algorithm which is well-suited for data that contains many runs of the same value or small differences between consecutive values.

example:

``` bash
Given text: "aaabbbcc"
RLE compressed text: "a3b3c2"

explaination:
a3 -> 3 a's
b3 -> 3 b's
c2 -> 2 c's
```

Breakdown of the RLE algorithm:

- Encoding:

  1. Start from the beginning of the input data.
  2. Look for runs of the same value. (scan repeatedly data, a smallest fragment of data is called token)
  3. Replace each run with a single data value and a count of the number of times it occurs.
  4. Continue until the entire input data has been processed.
  5. Return the compressed data.

- Decoding:

  1. Start from the beginning of the compressed data.
  2. Read the next data value (token) and count.
  3. Repeat the data value count times.
  4. Continue until the entire compressed data has been processed.
  5. Return the decompressed data.
  6. The decompressed data should be the same as the original input data.

### Static Dictionary Coding

Static Dictionary coding is a lossless data compression algorithm that works by creating a dictionary of strings and replacing the duplicate strings with a reference to the dictionary. It is a form of substitution compression.

example:

``` bash
Given Dictionary: { "yesterday", "all", "my", "troubles", "seemed", "so", "far", "away", "easy", "game" }
Given text: "yesterday love was such an easy game to play"

Encoded text: "0 love was such an 8 9 to play"

explaination:
0 -> yesterday
8 -> easy
9 -> game
```

Breakdown of the Static Dictionary Coding algorithm:

- Encoding:
  
  1. Start from the beginning of the input data.
  2. Split the input data into tokens.
  3. Look up each token in the dictionary.
  4. Replace each token with a reference (aka coding) to the dictionary (for this case is index).
  5. Continue until the entire input data has been processed.
  6. Return the compressed data.

- Decoding:

  1. Start from the beginning of the compressed data.
  2. Read the next reference (index) to the dictionary.
  3. Look up the reference in the dictionary and replace it with the original token.
  4. Continue until the entire compressed data has been processed.
  5. Return the decompressed data.

## Benchmark

### Test Data

The test data are various lenght, for this given time, we'll use 3 types of following data:

1. Randomly repeated chars on string (e.g. "aaaaabbbbbcccccdeffffggjiiikll")
2. Full-text of wikipedia article to reflect the real-world data
3. DNA Sequence (e.g. "ATCGATCGATCGATCG"; block of 4 characters)

### Measurement

The performance of the RLE and Dictionary Coding algorithms will be measured using the following metrics:

1. Compression Ratio: The ratio of the size of the compressed data to the size of the original data. (< 100% means the data is reduced in size, > 100% means the data is increased in size)
2. Encoding Time: The time it takes to compress the data. (chrono nano second)
3. Decoding Time: The time it takes to decompress the data. (chrono nano second)
4. CPU/Memory Usage: The amount of memory used by the compressed data. (NOTE: this is not implemented yet, It's a good idea to measure the memory usage of the compressed data, but im quite struggle to find the way to measure it)

### Scenarios

The performance of the RLE and Dictionary Coding algorithms will be measured under the following scenarios:

1. For RLE, the scenarios will be:
   - Input one of [Randomly repeated chars on string, Full article from wikipedia, DNA Sequence]
   - Measure the compression ratio, encoding time, and decoding time.
   - Analyze the behavior of the algorithm under different scenarios.
   - Improves if possible.
2. For Dictionary Coding, the scenarios will be:
   - Input one of [Randomly repeated chars on string, Full article from wikipedia, DNA Sequence]
   - Measure the compression ratio, encoding time, and decoding time.
   - Analyze the behavior of the algorithm under different scenarios.
   - Improves if possible.
3. Compare both algorithms under the same scenarios. if possible, try to improve the algorithm & note the trade-off.

### Results

#### Scenario 1: Randomly repeated chars on string

``Input: "AAAAABBBBBCCCCCDDDDDACCXVXXXTTTTUAAUVVVVVWWWWWXXXXXYYYYYZZZZZ"``

- ``RLE Encoded: "5A5B5C5D1A2C1X1V3X4T1U2A1U5V5W5X5Y5Z"``
- ``SDC Encoded: "AAAAABBBBBCCCCCDDDDDACCXVXXXTTTTUAAUVVVVVWWWWWXXXXXYYYYYZZZZZ"``

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  |
|------------------|--------------------|----------------|----------------|
| RLE              | 0.59               | 6667 ns       | 3208 ns        |
| Static Dictionary| 1.01                | 17699208 ns        | 192625 ns        |

``Input: "ABCBBBCJJKKYSBROLMAOFFFJKLKKKKXJSJXKSHXHJSHXHSXHSXSHXSHXSH"``

- ``RLE Encoded: "1A1B1C3B1C2J2K1Y1S1B1R1O1L1M1A1O3F1J1K1L4K1X1J1S1J1X1K1S1H1X1H1J1S1H1X1H1S1X1H1S1X1S1H1X1S1H1X1S1H"``
- ``SDC Encoded: "ABCBBBCJJKKYSBROLMAOFFFJKLKKKKXJSJXKSHXHJSHXHSXHSXSHXSHXSH"``

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  |
|------------------|--------------------|----------------|----------------|
| RLE              | 1.68                | 24417 ns       | 17042 ns        |
| Static Dictionary| 1.01                | 17737583 ns        | 213583 ns        |

```footnotes: for static dictionary, the dictionary is static and contain the most common words in english language. It's not optimized for this case, but it's a good start to measure the performance of the algorithm.```

#### Scenario 2: Full sentence

``Input: "the man who sold the world said ooooh child things are gonna get easier"``

- ``RLE Encoded: "1t1h1e1 1m1a1n1 1w1h1o1 1s1o1l1d1 1t1h1e1 1w1o1r1l1d1 1s1a1i1d1 4o1h1 1c1h1i1l1d1 1t1h1i1n1g1s1 1a1r1e1 1g1o2n1a1 1g1e1t1 1e1a1s1i1e1r1"``
- ``SDC Encoded: "320693 178863 365280 296539 320693 367568 276752 ooooh 54286 321887 19298 127801 124420 94903"``

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  |
|------------------|--------------------|----------------|----------------|
| RLE              | 1.88                | 32542 ns        | 18291 ns        |
| Static Dictionary| 1.32                | 92662459 ns        | 129208 ns        |

#### Scenario 3: DNA Sequence

``Input: <fileplaceholder>``

- ``RLE Encoded: <fileplaceholder>``
- ``SDC Encoded: <fileplaceholder>``

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  |
|------------------|--------------------|----------------|----------------|
| RLE              | 1.71                | 285459 ns        | 212083 ns        |
| Static Dictionary| 0.71                | 1923334 ns        | 102334 ns        |

### Hipotesis & Conclusion

... todo

## Improvesment

... todo

## Known Issues

- The scope of the project is limited to string & alphabet characters only. It'll break if the input data contains special characters or numbers. (it'll be fixed if we change the "coding" instead of number into custom special token like `#A{index}A#`, but it's trade-off with the compression ratio)
