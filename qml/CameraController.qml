import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Logic 2.0
import QtQml 2.2
import QtGamepad 1.0

Entity {
    id: root
    property Camera camera
    property real linearSpeed: 10.0
    property real lookSpeed: 181.0

    QtObject {
        id: d
        readonly property vector3d firstPersonUp: Qt.vector3d(0, 1, 0)
        readonly property bool leftMouseButtonPressed: leftMouseButtonAction.active
        readonly property real vx: txAxis.value * linearSpeed;
        readonly property real vy: tyAxis.value * linearSpeed;
        readonly property real vz: tzAxis.value * linearSpeed;
        readonly property real dx: rxAxis.value * lookSpeed
        readonly property real dy: ryAxis.value * lookSpeed
        readonly property bool fineMotion: fineMotionAction.active
    }

    KeyboardDevice {
        id: keyboardSourceDevice
    }

    MouseDevice {
        id: mouseSourceDevice
        sensitivity: d.fineMotion ? 0.01 : 0.1
    }

    components: [

        LogicalDevice {
            actions: [
                Action {
                    id: leftMouseButtonAction
                    inputs: [
                        ActionInput {
                            sourceDevice: mouseSourceDevice
                            buttons: [MouseEvent.LeftButton]
                        }
                    ]
                },
                Action {
                    id: fineMotionAction
                    inputs: [
                        ActionInput {
                            sourceDevice: keyboardSourceDevice
                            buttons: [Qt.Key_Shift]
                        }
                    ]
                }
            ] // actions

            axes: [
                // Rotation
                Axis {
                    id: rxAxis
                    AnalogAxisInput {
                        sourceDevice: mouseSourceDevice
                        axis: MouseDevice.X
                    }
                },
                Axis {
                    id: ryAxis
                    AnalogAxisInput {
                        sourceDevice: mouseSourceDevice
                        axis: MouseDevice.Y
                    }
                },
                // Translation
                Axis {
                    id: txAxis
                    inputs: [
                        ButtonAxisInput {
                            sourceDevice: keyboardSourceDevice
                            buttons: [Qt.Key_Left, Qt.Key_A]
                            scale: -1.0
                        },
                        ButtonAxisInput {
                            sourceDevice: keyboardSourceDevice
                            buttons: [Qt.Key_Right, Qt.Key_D]
                            scale: 1.0
                        }
                    ]
                },
                Axis {
                    id: tzAxis
                    inputs: [
                        ButtonAxisInput {
                            sourceDevice: keyboardSourceDevice
                            buttons: [Qt.Key_Up, Qt.Key_W]
                            scale: 1.0
                        },
                        ButtonAxisInput {
                            sourceDevice: keyboardSourceDevice
                            buttons: [Qt.Key_Down, Qt.Key_S]
                            scale: -1.0
                        }
                    ]
                },
                Axis {
                    id: tyAxis
                    inputs: [
                        ButtonAxisInput {
                            sourceDevice: keyboardSourceDevice
                            buttons: [Qt.Key_PageUp]
                            scale: 1.0
                        },
                        ButtonAxisInput {
                            sourceDevice: keyboardSourceDevice
                            buttons: [Qt.Key_PageDown]
                            scale: -1.0
                        }
                    ]
                }
            ] // axes
        },

        FrameAction {
            onTriggered: {
                // The time difference since the last frame is passed in as the
                // argument dt. It is a floating point value in units of seconds.
                root.camera.translate(Qt.vector3d(d.vx, d.vy, d.vz).times(dt))
                if (d.leftMouseButtonPressed) {
                    root.camera.pan(d.dx * dt, d.firstPersonUp)
                    root.camera.tilt(d.dy * dt)
                }
            }
        }
    ] // components

    Connections {
        target: GamepadManager
        onGamepadConnected: gamepad.deviceId = deviceId
    }

    Gamepad {
        id: gamepad
        deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1
    }
}

