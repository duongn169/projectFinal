import numpy as np
import pandas as pd
from flask import Flask, request, render_template
import pickle


model = pickle.load(open('trained_model.pkl', 'rb'))




inputValue = [22,1,32,66,86,23,55,66]


def predict():
    input_features = inputValue
    features_value = [np.array(input_features)]

    features_name = ["age", "sex", "cp", "trestbps",
                     "thalach",  "exang", "ca", "thal"]

    df = pd.DataFrame(features_value, columns=features_name)
    output = model.predict(df)

    if output == 1:
        res_val = "** heart disease **"
    else:
        res_val = "no heart disease "

    return res_val


text = predict()
print(text)
