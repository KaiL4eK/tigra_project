ROSLIB = src/ros_lib
include $(ROSLIB)/ros.mk

PROJECT_MODULES = src/lld_brake_sensor.c        \
                  src/lld_clutch_lever.c        \
                  src/lld_control.c             \
                  src/lld_steer_sensors.c       \
                  src/lld_wheel_pos_sensor.c    \
                  src/lld_sonars.c              \
                  src/brake_unit_cs.c           \
                  src/drive_speed_cs.c 			\
                  src/controllers.c				\
                  src/steer_unit_cs.c			\
                  src/light_unit.c				\
                  src/base_control_unit.c
                  
PROJECT_TESTS   = tests/test_brake_sensor.c     \
                  tests/test_clutch_lever.c     \
                  tests/test_lld_control.c      \
                  tests/test_lld_steer_sensors.c\
                  tests/test_wheel_pos_sensor.c \
                  tests/test_ros_driver.c       \
                  tests/test_lld_sonars.c       \
                  tests/test_brake_unit_cs.c    \
                  tests/test_drive_speed_cs.c	\
                  tests/test_lightning.c		\
                  tests/test_tools.c			\
                  tests/test_steer_unit_cs.c	\
                  tests/test_steer_power.c

PROJECT_CSRC    = src/main.c src/common.c \
                    $(PROJECT_MODULES) $(PROJECT_TESTS)
                    
PROJECT_CPPSRC  = $(ROSSRC) src/ros.cpp

PROJECT_INCDIR  = include tests $(ROSINC)

PROJECT_LIBS    = -lm
