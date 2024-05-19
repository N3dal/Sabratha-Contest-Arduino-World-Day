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
import json

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


class Report(db.Model):
    """
        Docstring;
    """
    id = db.Column(db.Integer, primary_key=True)
    bus_id = db.Column(db.String(200), nullable=False)
    driver_id = db.Column(db.String(200), default="Empty")
    driver_name = db.Column(db.String(200), default="Empty")
    engine_state = db.Column(db.Integer, default="Empty")
    collision_state = db.Column(db.Integer, default="Empty")
    tilt_state = db.Column(db.Integer, default="Empty")
    motor_speed_level = db.Column(db.Integer, default="Empty")
    seat_belt_state = db.Column(db.Integer, default="Empty")
    system_state = db.Column(db.Integer, default="Empty")
    record_date = db.Column(db.DateTime, default=datetime.now())


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


@ app.route("/login", methods=[POST, GET])
@ app.route("/", methods=[POST, GET])
def login():
    message = ""
    if request.method == POST and "username" in request.form and "password" in request.form:
        username = request.form["username"]
        password = request.form["password"]

        if username == "admin" and password == "admin":
            all_reports = Report.query.order_by(Report.record_date).all()
            print(f"[+] {all_reports}")
            return render_template("index.html", server_ip=server_ip, reports=all_reports)
        else:
            return redirect("login")
    else:
        pass

    return render_template(r"login.html")


@ app.route("/send_data", methods=[POST])
def send_data():
    global nodes_data
    json_data = request.get_json()

    nodes_data[json_data["bus-id"]] = json_data
    print(f"[+]  {json_data}")

    for bus_name, json_data in nodes_data.items():
        if json_data is None:
            pass

        else:
            data_to_log = Report(
                bus_id=json_data["bus-id"],
                driver_id=json_data["driver-id"],
                driver_name=json_data["driver-name"],
                engine_state=json_data["engine-state"],
                collision_state=json_data["collision-state"],
                tilt_state=json_data["tilt-state"],
                motor_speed_level=json_data["motor-speed-level"],
                seat_belt_state=json_data["seat-belt-state"],
                system_state=json_data["system-state"],
                record_date=datetime.now()
            )
            pass

        # try:
        # app.app_context().push()
        db.session.add(data_to_log)
        db.session.commit()

        # except Exception as e:
        #     print(f"[+]     can't add new data to db!!! {e}")

    return ""


@ app.route("/get_data", methods=[GET])
def get_data():
    global nodes_data
    current_data = nodes_data.copy()
    nodes_data = {
        "BUS-0001": None,
        "BUS-0002": None
    }

    return jsonify(current_data)


@ app.route("/settings")
def settings():
    with open("./.settings.json", "r") as file:
        settings_data = json.load(file)

    seat_belt_fine_price = settings_data["seat-belt-fine-price"]
    over_speed_limit_price = settings_data["over-speed-limit-fine-price"]

    return render_template("settings.html", seat_belt_fine_price=seat_belt_fine_price, over_speed_limit_price=over_speed_limit_price)


@ app.route("/save_settings", methods=[POST])
def save_settings():
    message = ""
    if request.method == POST:
        seat_belt_fine_price = request.form["seat-belt-fine"]
        over_speed_limit_fine_price = request.form["over-speed-limit-fine"]

        settings_data = {
            "seat-belt-fine-price": seat_belt_fine_price,
            "over-speed-limit-fine-price": over_speed_limit_fine_price
        }

        with open(".settings.json", "w") as file:
            json.dump(settings_data, file)
    else:
        print("[+] Not enter")
        pass

    return redirect("/settings", code=302)


@ app.route("/about")
def about():
    return render_template("about.html")


@ app.route("/print_fine/<int:id>", methods=[GET])
def print_fine(id):

    fine = Report.query.get_or_404(id)

    with open("./.settings.json", "r") as file:
        settings_data = json.load(file)

    seat_belt_fine_price = settings_data["seat-belt-fine-price"]
    over_speed_limit_price = settings_data["over-speed-limit-fine-price"]

    return render_template("fine.html", fine=fine, seat_belt_fine_price=seat_belt_fine_price, over_speed_limit_price=over_speed_limit_price)


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
