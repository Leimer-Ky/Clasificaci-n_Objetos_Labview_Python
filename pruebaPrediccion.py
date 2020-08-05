print("Iniciando Sistema.....")
import numpy as np
import cv2
import time
from tensorflow.keras.preprocessing.image import load_img, img_to_array
from tensorflow.keras.models import load_model

longitud, altura = 150, 150
modelo = './modelo/modelo3_project.h5'
pesos_modelo = './modelo/pesos3_project.h5'
cnn = load_model(modelo)
cnn.load_weights(pesos_modelo)

result = ''
print("Sistema Iniciado.....")
def predict(file):
  x = load_img(file, target_size=(longitud, altura))
  #plt.imshow(x)
  #plt.show()
  #x = plt.imread(file)
  #x= cv2.resize(x,(longitud_m1_m3,altura_m1_m3))
  #x= cv2.cvtColor(x,cv2.COLOR_BGR2GRAY)
  x = img_to_array(x)
  x = np.expand_dims(x, axis=0)
  array = cnn.predict(x)
  print(array)
  result = array[0]
  print (result)
  answer = np.argmax(result)
 
  if answer == 0:
    result = 'nano'
    print("pred: Nano")
  elif answer == 1:
    result = 'uno'
    print("pred: Uno")
  else:
    print("Desconocido")

  return result

predict('uno.jpg')
time.sleep(15)

