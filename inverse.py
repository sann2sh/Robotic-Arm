import matplotlib.pyplot as plt
import numpy as np
import math

def inverse_kinematics(x, y, l1, l2):
    """
    Calculate the joint angles for a 2-DOF robotic arm using inverse kinematics.
    """
    r = math.sqrt(x**2 + y**2)

    if r > (l1 + l2) or r < abs(l1 - l2):
        raise ValueError("Target position is out of reach")

    cos_theta2 = (x**2 + y**2 - l1**2 - l2**2) / (2 * l1 * l2)
    sin_theta2 = math.sqrt(1 - cos_theta2**2)
    theta2 = math.atan2(sin_theta2, cos_theta2)
    k1 = l1 + l2 * cos_theta2
    k2 = l2 * sin_theta2
    
    theta1 = math.atan2(y, x) - math.atan2(k2, k1)

    return theta1, theta2

def forward_kinematics(theta1, theta2, l1, l2):
    """
    Calculate the (x, y) positions of the joints and end effector.
    """
    x1 = l1 * math.cos(theta1)
    y1 = l1 * math.sin(theta1)
    x2 = x1 + l2 * math.cos(theta1 + theta2)
    y2 = y1 + l2 * math.sin(theta1 + theta2)
    return (0, x1, x2), (0, y1, y2)

# Visualization setup
l1 = 13
l2 = 19

fig, ax = plt.subplots()
ax.set_xlim(-l1 - l2 - 1, l1 + l2 + 1)
ax.set_ylim(-l1 - l2 - 1, l1 + l2 + 1)
ax.set_aspect('equal')
ax.set_title("2-DOF Robotic Arm (Click to Move)")

# Enable grid
ax.grid(True, which='both', linestyle='--', linewidth=0.5, color='gray')

arm_line, = ax.plot([], [], 'o-', lw=2)  # Arm line
text_angles = ax.text(0.05, 0.95, "", transform=ax.transAxes, ha="left", va="top")

def onclick(event):
    try:
        x, y = event.xdata, event.ydata
        if x is None or y is None:
            return  # Ignore clicks outside the plot
        theta1, theta2 = inverse_kinematics(x, y, l1, l2)
        x_points, y_points = forward_kinematics(theta1, theta2, l1, l2)
        arm_line.set_data(x_points, y_points)
        text_angles.set_text(
            f"θ1: {math.degrees(theta1):.2f}°\nθ2: {math.degrees(theta2):.2f}°"
        )
        fig.canvas.draw()
    except ValueError as e:
        text_angles.set_text(str(e))
        fig.canvas.draw()

fig.canvas.mpl_connect('button_press_event', onclick)

# Draw the initial arm position
theta1, theta2 = 0, 0
x_points, y_points = forward_kinematics(theta1, theta2, l1, l2)
arm_line.set_data(x_points, y_points)

plt.show()
