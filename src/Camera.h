#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Core>

#include "types.h"

class Camera
{
public:
  /** Physical position of the camera */
  Point position;
  /** Point at which the camera is looking at */
  Point lookAt;
  /** Distance from the camera to the screen (in meters) */
  float d;
  /** Field of view of the camera (in radians) */
  float fov;
  /** Aspect ratio: screen width divided by screen height */
  float aspectRatio;

  /**
   * View matrix in homogeneous coordinates
   * Allows to go from scene coordinates to camera coordinates
   * by left matrix multiplication
   * @TODO check that it's not the other way around...
   */
  Eigen::Matrix4f viewMatrix;

  /** Default parameters */
  static Point const DEFAULT_POSITION;
  static Point const DEFAULT_LOOK_AT;
  static float const DEFAULT_DISTANCE;
  static float const DEFAULT_FOV;
  static float const DEFAULT_ASPECT_RATIO;

  /**
   * @param p Position of the camera
   * @param l Point at which the camera is looking at
   */
  Camera(Point const & p = DEFAULT_POSITION,
         Point const & l = DEFAULT_LOOK_AT,
         float distance = DEFAULT_DISTANCE,
         float fieldOfView = DEFAULT_FOV,
         float ratio = DEFAULT_ASPECT_RATIO);

protected:
  /** Screen dimensions (in meters) */
  float screenWidth, screenHeight;

  /** Update `viewMatrix` based on
   * position, lookAt, distance to screen and field of view
   */
  void computeViewMatrix();
};

#endif
