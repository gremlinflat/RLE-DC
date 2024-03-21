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

1. Randomly repeated chars on string (e.g. ```aaaaabbbbbcccccdeffffggjiiikll```)
2. Full-text of wikipedia article to reflect the real-world data
3. DNA Sequence (e.g. ```GACC ATGT AAAA CATT TGTT ACAA GTCT```; block of 4 characters)

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
```Static Dictionary for DC:``` [English_Alpha](https://github.com/gremlinflat/RLE-DC/blob/master/test/english_dictionary_alpha.txt)

- ``RLE Encoded: "1t1h1e1 1m1a1n1 1w1h1o1 1s1o1l1d1 1t1h1e1 1w1o1r1l1d1 1s1a1i1d1 4o1h1 1c1h1i1l1d1 1t1h1i1n1g1s1 1a1r1e1 1g1o2n1a1 1g1e1t1 1e1a1s1i1e1r1"``
- ``SDC Encoded: "320693 178863 365280 296539 320693 367568 276752 ooooh 54286 321887 19298 127801 124420 94903"``

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  |
|------------------|--------------------|----------------|----------------|
| RLE              | 1.88                | 32542 ns        | 18291 ns        |
| Static Dictionary| 1.32                | 92662459 ns        | 129208 ns        |

#### Scenario 3: DNA Sequence

``Input:``[single DNA Sequence](https://github.com/gremlinflat/RLE-DC/blob/master/test/input_single_DNA.txt)
```Static Dictionary for DC:``` [DNA Combination (4 char chunks)](https://github.com/gremlinflat/RLE-DC/blob/master/test/dna_dictionary.txt)

- ``RLE Encoded:`` [RLE single DNA Result](https://github.com/gremlinflat/RLE-DC/blob/f2ec7a09485d874de67e2e154bf366ce62105e71/test/result/rle_dna_single.txt)
- ``SDC Encoded:`` [SDC single DNA Result](https://github.com/gremlinflat/RLE-DC/blob/master/test/result/sdc_dna_single.txt)

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  |
|------------------|--------------------|----------------|----------------|
| RLE              | 1.71                | 285459 ns        | 212083 ns        |
| Static Dictionary| 0.71                | 1923334 ns        | 102334 ns        |

### Hipotesis & Conclusion

- RLE is better for the data that contains many runs of the same value or small differences between consecutive values. It's not suitable for the full-text data, but it's good for repeating sequence of data such as DNA Sequence.
- Static Dictionary Coding is better for the full-text data, but it's not suitable for the repeating sequence of data such as DNA Sequence. It's also not suitable for the random repeating chars on string, because the dictionary is not optimized for this case.
- The encoding & decoding time of the Static Dictionary Coding is significantly higher than the RLE (due to dictionary look up; this part is seems promising to deep dive into), but the compression ratio is better for the full-text data. It's not suitable for the random repeating chars on string, because the dictionary is not optimized for this case.
- The compression ratio of the RLE is better for the random repeating chars on string, but it's not suitable for the full-text data. It's also not suitable for the DNA Sequence, because the data is not repeating sequence of data.
- The compression ratio of the Static Dictionary Coding is better for the full-text data, but it's not suitable for the random repeating chars on string. It's also not suitable for the DNA Sequence, because the dictionary is not optimized for this case.

#### Problem statement

- [RLE-I1] RLE is quite good for the repeating sequence of data even though it's not suitable for the full-text data. As the result, it's quite not good for unique sequence of data and high chance to increase the size of the data. e.g. ```abcdeffg``` will be encoded into ```1a1b1c1d1e2f1g``` which is larger than the original data.
- [DC-I1] Static Dictionary Coding is quite good for the full-text data even though it's not suitable for the repeating sequence of data. As the result, even though all the data is unique, it's still able to compress the data but the compression ratio is not increasing significantly. e.g. ```abcdeffg``` will be encoded into ```abcdeffg``` which is the same size as the original data. ```as a foot note, the dictionary is still increasing the data size, so the dictionary itself is an overhead for real world implementation```

## Improvesment Effort

- [RLE-I1] To solve this problem, My no-brainer solution is to remove a counter if the counter is 1. e.g. ```abcdeffg``` will be encoded into ```abcde2f1g``` which is smaller than the original data. This is a good start to improve the compression ratio of the RLE algorithm. The trade-off is the encoding time will be increased because we need to check the counter for each token. Therefore, I've implemented it on RLEV2 (an improved version of RLE).
- [DC-I1] One of my solution is to make the algorithm learn the data and create the dictionary based on the data. Theres a lot of algorithm to do this, but for this given time, I'll use the simple one. which is by counting each frequency of the token and create the dictionary based on the threshold. e.g. given the dataset is ```word1 word2 word3 word1 word2 word3 word3 word4``` then the frequency of the token is ```word1: 2, word2: 2, word3: 3, word4: 1```. then the threshold is 0.8, so we'll create the dictionary based on top 80% of the frequency. The dictionary will be ```{word3, word1, word2}```. The trade-off is that we need good amount of variation of the data to create the dictionary, but it's a good start to improve the compression ratio of the Static Dictionary Coding algorithm. Therefore, I've implemented it a method to generate the custom dynamic dictionary based on the data.

### Result of the Improved Algorithm

#### [RLE-I1] Improved RLE

TLDR Goals: to remove an overhead of the counter if the counter is 1.

``Input: "ABCBBBCJJKKYSBROLMAOFFFJKLKKKKXJSJXKSHXHJSHXHSXHSXSHXSHXSH"``

- ``RLE Encoded: "1A1B1C3B1C2J2K1Y1S1B1R1O1L1M1A1O3F1J1K1L4K1X1J1S1J1X1K1S1H1X1H1J1S1H1X1H1S1X1H1S1X1S1H1X1S1H1X1S1H"``
- ``RLEV2 Encoded: "ABC3BC2J2KYSBROLMAO3FJKL4KXJSJXKSHXHJSHXHSXHSXSHXSHXSH"``

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  |
|------------------|--------------------|----------------|----------------|
| RLE              | 1.68                | 24417 ns       | 17042 ns        |
| RLEV2            | 0.93                | 10250 ns       | 12875 ns        |

#### [DC-I1] Dynamic Dictionary Coding

TLDR Goals: to create the dictionary based on the similar data.

```Input:``` [full-text wikipedia article 1](https://github.com/gremlinflat/RLE-DC/blob/master/test/input_wiki.txt)

```Dataset for the dictionary:``` [full-text wikipedia article 2](https://github.com/gremlinflat/RLE-DC/blob/master/test/input_wiki2.txt)

- ``Static DC Encoded:`` [Static DC wiki result](https://github.com/gremlinflat/RLE-DC/blob/master/test/result/sdc_wiki.txt)
- ``Dynamic DC Encoded (threshold: 0.8):`` [Dynamic DC (0.8) wiki result](https://github.com/gremlinflat/RLE-DC/blob/master/test/result/ddc_wiki08.txt)
- ``Dynamic DC Encoded (threshold: 0.6):`` [Dynamic DC (0.6) wiki result](https://github.com/gremlinflat/RLE-DC/blob/master/test/result/ddc_wiki06.txt)

| Algorithm        | Compression Ratio  | Encoding Time  | Decoding Time  | Learning Time | Dictionary Size | Dictionary |
|------------------|--------------------|----------------|----------------|----------------|-----------------| -----------|
| Static DC        | 1.09                | 3582884917 ns        | 3168250 ns        | - | 3.864.812 bytes  | [English_Alpha](https://github.com/gremlinflat/RLE-DC/blob/master/test/english_dictionary_alpha.txt) |
| Dynamic DC (0.8) | 0.85                | 3704417 ns        | 3916500 ns        | 904250 ns | 2.433 bytes | [wiki2_08](https://github.com/gremlinflat/RLE-DC/blob/master/test/result/dict/wiki08.txt) |
| Dynamic DC (0.6) | 0.86                | 5895000 ns        | 6969792 ns        | 2729125 ns | 6 | [wiki2_06](https://github.com/gremlinflat/RLE-DC/blob/master/test/result/dict/wiki06.txt) |

## Conclusion

We've improved the RLE algorithm by removing the overhead of the counter if the counter is 1. The result is quite promising, the compression ratio is increased significantly and the encoding time is decreased. The trade-off is the encoding time is increased because we need to check the counter for each token.

Also, we've improved the Static Dictionary Coding algorithm by creating the dictionary based on the similar data. The result is quite promising, the compression ratio is increased significantly and the encoding time is decreased. The trade-off is the encoding time is increased because we need to learn the data and create the dictionary based on the data.

However, Compression Algorithm is highly contextual and depends on the data. Theres no silver bullet for the data compression algorithm. The performance of the algorithm is highly dependent on the data. Therefore, we need to understand the data and choose the right algorithm for the data.

## Known Issues

- The scope of the project is limited to string & alphabet characters only. It'll break if the input data contains special characters or numbers. (it'll be fixed if we change the "coding" instead of number into custom special token like `#A{index}A#`, but it's trade-off with the compression ratio)
