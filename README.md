# CLI Docs Search (tf-idf) Engine

This program implements a Command Line Interface (CLI) document search engine based on the Term Frequency-Inverse Document Frequency (tf-idf) algorithm. It searches for the occurrence of specific terms within documents and ranks them based on their relevance.

## Features

- **Search Functionality**: Enter a term or phrase to search for within the documents.
- **tf-idf Calculation**: Calculates tf-idf scores for the searched terms across documents.
- **Sorting**: Sorts documents based on tf-idf scores.
- **Document Viewing**: Displays the path of the most relevant document containing the searched term.
- **Continuous Search**: Allows for continuous searching without exiting the program.

## Usage

1. **Input Term to Search**: Enter the term or phrase you want to search for.
2. **Results Display**: View the tf-idf scores for each document containing the searched term.
3. **Document Viewing**: Access the most relevant document by clicking on the displayed path.

## How to Run

To run the program:

1. Compile the code using a C compiler.
2. Execute the compiled program.
3. Follow the on-screen instructions to search for documents.

## Requirements

- C compiler (e.g., gcc)
- Standard C libraries (assert.h, stdio.h, stdlib.h, dirent.h, string.h)

## Example

```bash
$ ./search_engine
> Input term you want to search:
> algorithm
```
## Notes
Make sure the documents you want to search are located in the specified directory ("a\\" in this case).
