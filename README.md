# CapchaNN

## Dependencies
- OpenCV 3 https://opencv.org/
: Used for image preprocessing
- Fast Artificial Neural Network Library http://leenissen.dk/fann/wp/
: Implements an ANN

## Building
`make GenerateTraining`
`make TrainFann`
`make SanityTest`

## Running
`./GenerateTraining [config file]`
: Generates a training file to be used by FANN
: The config file simply lists an image location and a label for the capcha image separated by a comma.
`TrainFann [trainingData.txt] [NetworkName.net]`
: Trains FANN using the trainingData.txt and saves the ANN to NetworkName.net.
`SanityTest`
: Test on a small sample
