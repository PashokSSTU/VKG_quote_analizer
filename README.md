# VKG quote-analizer

### Description
`quote-analizer` is a program that creates .csv files of quotes in the format of Japanese candlesticks and SMAs for a specified period at closing prices

*Calling example:*
```
quote-analizer -l 5 -p 50 -f <path_to_input_file>.csv -o <path_to_output_directory> 
```

The result of the utility execution is written to a .csv files `candles.csv` and `sma_values.csv`

### Building
1. Invoke this command to install the required packages:
```
sudo dnf group -y install "C Development Tools and Libraries" "Development Tools"
sudo dnf -y install git cmake make ninja-build cxxopts
```

2. Clone the repository and go to it. After that, call the build script:
```
cd <path to directiry>/VKG_quote_analizer/
sudo ./build.sh
```
3. Wait for project build;
4. The assembled utility is installed automatically after the assembly is called. The executable is installed in a directory according to the FHS standard.


