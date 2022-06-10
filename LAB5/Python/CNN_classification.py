import numpy as np
import numpy as torch
import torch
import torch.nn as nn
import torchvision
import pandas as pd
import os
from PIL import Image
toTensor = torchvision.transforms.ToTensor()
imResize = torchvision.transforms.Resize((150, 150))


class CNN(nn.Module):
    def __init__(self, cnn_layers=2, cnn_channels=32, kernel_size=3, cnn_act_fcn=nn.Sigmoid(), hidden_layer_list=[],
                 lin_act_fcn=nn.Sigmoid(), drop_c=0):
        super().__init__()
        image_dimension = 150
        # Convolutional layer

        input_channels = 3
        out_channels = cnn_channels
        cnn_model_list = []
        for layer in range(cnn_layers):
            # Convolutional layer
            cnn_model_list.append(nn.Conv2d(input_channels, out_channels, kernel_size, padding="same"))
            # Activation function
            cnn_model_list.append(cnn_act_fcn)
            # Pooling layer
            cnn_model_list.append(nn.MaxPool2d(kernel_size=2))
            # Dropout
            cnn_model_list.append(nn.Dropout(drop_c))
            input_channels = out_channels
            image_dimension = image_dimension // 2  # Pooling layer reduces the actual image dimension.
        self.cnn_model = nn.Sequential(*cnn_model_list)
        # Linear network

        self.num_classes = 2
        input_dim = int(input_channels * (image_dimension) ** 2)
        out_dim = self.num_classes
        layers = []
        for num_nodes in hidden_layer_list:
            output_dim = num_nodes
            # Layer size
            layers.append(nn.Linear(input_dim, output_dim))
            # Dropout
            layers.append(nn.Dropout(drop_c))
            # Activation function
            layers.append(lin_act_fcn)
            input_dim = output_dim
        layers.append(nn.Linear(input_dim, out_dim))
        self.linear_model = nn.Sequential(*layers)

    def forward(self, x):
        softmax = nn.Softmax(dim=-1)
        out = self.cnn_model(x)
        if len(out.shape) == 4:
            out = out.view(out.size(0), -1)
        else:
            out = torch.flatten(out)
        out = self.linear_model(out)
        return softmax(out)

    def print_modules(self):
        print("Classification network:")
        print("CNN modules:\n{}".format(self.cnn_model))
        print("Linear modules:\n{}".format(self.linear_model))


python_path = "/home/edoardo/Desktop/Computer-Vision/LAB5/Python/"
os.chdir(python_path)
net = torch.load("CNN_model.pkl")
net.eval()
img_path = "/home/edoardo/Pictures/Computer-Vision/LAB5/full_img/splitted/"
os.chdir(img_path)

pd_dataframe_list = []
for file in os.listdir(img_path):
    filename, ext = os.path.splitext(file)
    if ext == '.csv' and filename != "image_linker":
        pd_dataframe = pd.read_csv(file)
        image_name_list = pd_dataframe["Park Slot Image"]
        classification_res = []
        for image_filename in image_name_list:
            image = Image.open(image_filename)
            image = imResize(image)
            image_tensor = toTensor(image)
            net_out = net.forward(image_tensor)
            net_out_array = net_out.detach().numpy()
            net_class = np.argmax(net_out_array)
            classification_res.append(net_class)
        pd_dataframe["Classification Result"] = classification_res
        print(pd_dataframe)
        pd_dataframe.to_csv(file)

