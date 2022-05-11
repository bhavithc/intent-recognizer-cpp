# intent-recognizer-cpp
Intent recognizer command line tool, The input and output looks like this:

```
What is the weather like today? => Prints (Intent: Get Weather)
What is the weather like in Paris today? => Prints (Intent: Get Weather City)
Tell me an interesting fact. => Prints (Intent: Get Fact)
```

# Usage
This is a command line tool, So user has to provide his request via command line
```bash
$ IntentRecognizer What is the weather like today?
```
where:
    
    IntentRecognizer - Name of the program
    What is the weather like today? - User entered sentence

# How to make custom changes to the model
The entire IntentRecognizer depends on the `database.json` which is present under `/etc/` directory with read write permission.

Format of the json is as below
```json
{
    "data": {
        "intent": [
            "word1",
            "word2",
            "wordN",
        ]
    }
}
```
In the above json file, user can add as many intents as he wants with the words related to it. 

### default datatbase is 
```json
{
    "data": {
        "City": [
            "Paris",
            "France",
            "India",
            "Germany"
        ],
        "Weather": [
            "Weather"
        ],
        "Fact": [
            "Fact"
        ]
    }
}
```
Above `/etc/database.json` only handles the example sentences given below
```
What is the weather like today? => Prints (Intent: Get Weather)
What is the weather like in Paris today? => Prints (Intent: Get Weather City)
Tell me an interesting fact. => Prints (Intent: Get Fact)
```

Let's say user wants to support following example
```
Can you please help me? => Prints (Intent: Get help)
I need to know the weather? => Prints (Intent: Get weather help)
Is there any support on the issue? => Prints (Intent: Get help)
```
Now updated json looks like this
```json
{
    "data": {
        "City": [
            "Paris",
            "France",
            "India",
            "Germany"
        ],
        "Weather": [
            "Weather"
        ],
        "Fact": [
            "Fact"
        ],
        "Help": [
            "supoort",
            "need",
            "help"
        ]
    }
}
```

## Cmake build steps

### Configure cmake
```
cmake -H. -Bbuild
```

### Configure with debug flag enabled
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug
```

### Build
```
cmake --build build
```

### Executing unit test cases
```
cmake --build build --target test
```

### Installing
```
cmake --build build --target install
```
sudo is required in case permission not present
```
sudo cmake --build build --target install
```

### clean
```
rm -rf build
```

## Dependencies
```
sudo apt install qtbase5-dev
sudo apt-get install cmake
```
