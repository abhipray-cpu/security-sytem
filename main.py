import logging
import datetime as dt
from PyQt5 import QtWidgets, uic
from PyQt5.QtCore import Qt
from PyQt5 import QtWebEngineWidgets
import sys
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import os
import time
try:
    print(os.environ['DATABASE_URI'])
    # Fetch the service account key JSON file contents
    cred = credentials.Certificate('./configKey.json')
    # Initialize the app with a service account, granting admin privileges
    firebase_admin.initialize_app(cred, {
        'databaseURL': f"{os.environ['DATABASE_URI']}"
    })
    # declaring the collection objects
    Store = db.reference('/security')

except Exception as e:
    print(e)
# this the development log file
logging.basicConfig(filename="dev.log", level=logging.INFO)


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        uic.loadUi('view.ui', self)
        self.setWindowTitle('Monitor')
        self.axis1.setMinimum(0)
        self.axis1.setMaximum(180)
        self.axis2.setMinimum(0)
        self.axis2.setMaximum(180)
        self.axis1.setValue(90)
        self.axis2.setValue(100)

        self.axis1.valueChanged.connect(self.axis1Controller)
        self.axis1.setWrapping(False)
        self.axis2.setWrapping(False)
        self.axis2.valueChanged.connect(self.axis2Controller)
        self.play.clicked.connect(self.playController)
        self.record.clicked.connect(self.recordController)
        self.repeat.clicked.connect(self.repeatController)

    def axis1Controller(self):
        try:
            if 0 < self.axis1.value() < 100:
                Store.child('axis1').set(self.axis1.value())
                print(self.axis1.value())
        except Exception as e:
            logging.info(f'Failed to push data to axis1: {dt.datetime.now()}')
            logging.error(e)

    def axis2Controller(self):
        try:
            if 0 < self.axis2.value() < 100:
                Store.child('axis2').set(self.axis2.value())
                print(self.axis2.value())
        except Exception as e:
            logging.info(f'Failed to push data to axis2: {dt.datetime.now()}')
            logging.error(e)

    def playController(self):
        Store.child('play').set(1)

    def recordController(self):
        Store.child('record').set(1)

    def repeatController(self):
        Store.child('repeat').set(1)



def extiApp():
    app = QtWidgets.QApplication(sys.argv)

    try:
        Store.child('axis1').set(0)
    except Exception as e:
        logging.info(f'Failed to reset Axis1 value to zero: {dt.datetime.now()}')
        logging.error(e)

    try:
        Store.child('axis2').set(0)
    except Exception as e:
        logging.info(f'Failed to reset Axis2 value to zero: {dt.datetime.now()}')
        logging.error(e)

    app.exec_()


try:
    app = QtWidgets.QApplication(sys.argv)
    main = MainWindow()
    main.show()
    sys.exit(extiApp())


except Exception as e:
    logging.info(f'App crashed: {dt.datetime.now()}')
    logging.error(e)
