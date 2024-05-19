#!/usr/bin/python3
# -----------------------------------------------------------------
#
#
#
#
# Author:N84.
#
# Create Date:Sat Oct 28 18:12:03 2023.
# ///
# ///
# ///
# -----------------------------------------------------------------
from flask import (Flask, request, redirect, url_for,
                   render_template, session, jsonify)
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
from defaults import *
from flask_cors import CORS
from math import isnan
from threading import Thread
import atexit
from time import sleep as delay
import socket

# # to control the access of the nodes-data global variable;
# data_lock = threading.Lock()

# timer_handler = threading.Timer(0, lambda x: None, [])

nodes_data = {
    "BUS-0001": None,
    "BUS-0002": None
}

server_ip = socket.gethostbyname(socket.gethostname())
print(f"the ip address: {server_ip}")


def create_app() -> Flask:
    app = Flask(__name__)

    # database config;
    app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///main_db.db"

    CORS(app)

    return app


# app = Flask(__name__)
app = create_app()
# # database config;
# app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///main_db.db"

# init the database;
db = SQLAlchemy(app)

# CORS(app)


class Log(db.Model):
    """
        Docstring;
    """
    id = db.Column(db.Integer, primary_key=True)
    bus_id = db.Column(db.String(200), nullable=False)
    driver_id = db.Column(db.String(200), default="Empty")
    driver_name = db.Column(db.String(200), default="Empty")
    engine_state = db.Column(db.String(200), default="Empty")
    collision_state = db.Column(db.String(200), default="Empty")
    motor_speed_level = db.Column(db.String(200), default="Empty")
    seat_belt_state = db.Column(db.String(200), default="Empty")
    system_state = db.Column(db.String(200), default="Empty")
    date = db.Column(db.DateTime, default=datetime.now())


def log_data() -> None:
    """
        log data every 300-second aka 05-minutes;

        return None
    """

    # while True:
    # for node_name, json_data in nodes_data.items():
    #     if json_data is None:
    #         data_to_log = Log(
    #             node_name=node_name,
    #             status="معطل",
    #             temperature="---",
    #             humidity="---",
    #             door_status="---",
    #             record_time=datetime.now()
    #         )

    #     else:
    #         data_to_log = Log(
    #             node_name=json_data["node-name"],
    #             status="متصل" if json_data["system-status"] else "معطل",
    #             temperature=str(json_data["temperature"]) + "°C",
    #             humidity=str(json_data["humidity"]) + "%",
    #             door_status="مغلق" if json_data["door-status"] else "مفتوح",
    #             record_time=datetime.now()
    #         )

    #     try:
    #         app.app_context().push()
    #         db.session.add(data_to_log)
    #         db.session.commit()

    #     except:
    #         print("can't add new data to db!!!")

    # delay(LOG_TIME)

    return None


@app.route("/login", methods=[POST, GET])
@app.route("/", methods=[POST, GET])
def login():
    message = ""
    if request.method == POST and "username" in request.form and "password" in request.form:
        username = request.form["username"]
        password = request.form["password"]

        if username == "admin" and password == "admin":
            return render_template("index.html", server_ip=server_ip)
        else:
            return redirect("login")
    else:
        pass

    return render_template(r"login.html")


@app.route("/send_data", methods=[POST])
def send_data():
    global nodes_data
    json_data = request.get_json()
    # for key, value in json_data.items():
    #     if type(value) is float and isnan(value):
    #         json_data[key] = "Nan"

    nodes_data[json_data["bus-id"]] = json_data
    print(f"[+]  {json_data}")
    # log_data()

    return ""


@app.route("/get_data", methods=[GET])
def get_data():
    global nodes_data
    current_data = nodes_data.copy()
    nodes_data = {
        "BUS-0001": None,
        "BUS-0002": None
    }

    return jsonify(current_data)


@app.route("/reports")
def reports():
    return "Reports Page"


@app.route("/settings")
def settings():

    return render_template("settings.html")


@app.route("/log")
def log():

    # log_data = Log.query.order_by(Log.node_name).all()

    # return render_template("log.html", log_data=log_data)
    return ""


@app.route("/about")
def about():
    return render_template("about.html")


def main():
    print(f"DEBUG: {server_ip}")
    log_thread = Thread(target=log_data, args=[])
    log_thread.daemon = True

    log_thread.start()

    # app.run(debug=True, host="0.0.0.0", port=8080)
    app.run(debug=True, host=server_ip, port=8080)


if __name__ == "__main__":
    app.app_context().push()
    db.create_all()
    main()
