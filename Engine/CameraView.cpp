/*
 * Author		:Sangmin Kim
 * File			:CameraView.cpp
 * Term			:2020 Spring
 * Class		:GAM250
 * Project		:GAM250 Project
 * Date			:2020/07/09
 * Description	:Source file for Camera View
 * copyright   All content ?2020 DigiPen (USA) Corporation, all rights reserved
 */


#include "CameraView.hpp"

 // For RightHanded_OriginCenter
 // You want to map (-w/2, w/2) to (-1,1) and (-h/2,h/2) to (-1,1)
 //           (w/2,h/2)                (1,1)
 //      +--------+             +--------+
 //      |        |             |        |
 //      | cam    |     --->    | ndc    |
 //      +--------+             +--------+
 // (-w/2,-h/2)              (-1,-1)
 //

 // For RightHanded_OriginBottomLeft
 // You want to map (0, w) to (-1,1) and (0,h) to (-1,1)
 //             (w,h)                  (1,1)
 //      +--------+             +--------+
 //      |        |             |        |
 //      | cam    |     --->    | ndc    |
 //      +--------+             +--------+
 //    (0,0)                 (-1,-1)
 //

 // For LeftHanded_OriginTopLeft
 // You want to map (0, w) to (-1,1) and (0,h) to (1,-1)
 //    (0,0)                 (-1,1)
 //      +--------+             +--------+
 //      |        |             |        |
 //      | cam    |     --->    | ndc    |
 //      +--------+             +--------+
 //             (w,h)                  (1,-1)
 //


void helper_set_ndc(matrix3& camtoNDC, CameraView::FrameOfReference frame_reference, vector2 display_size, float zoom = 1)
{
    if (frame_reference == CameraView::FrameOfReference::RightHanded_OriginBottomLeft)
    {
        camtoNDC =
        {
            2 / display_size.x * zoom, 0, -1,
            0, 2 / display_size.y * zoom, -1,
            0,0,1
        };

        camtoNDC = MATRIX3::transpose(camtoNDC);
    }
    else if (frame_reference == CameraView::FrameOfReference::RightHanded_OriginCenter)
    {
        camtoNDC =
        {
            2 / display_size.x * zoom, 0, 0,
            0, 2 / display_size.y * zoom, 0,
            0,0,1
        };
        camtoNDC = MATRIX3::transpose(camtoNDC);
    }
    else if (frame_reference == CameraView::FrameOfReference::LeftHanded_OriginTopLeft)
    {
        camtoNDC =
        {
            2 / display_size.x * zoom, 0, -1,
            0, -2 / display_size.y * zoom, 1,
            0,1,1
        };
        camtoNDC = MATRIX3::transpose(camtoNDC);
    }
}

void CameraView::SetViewSize(vector2 pixel_size) noexcept
{
    displaySize = pixel_size;
    cameraToNDC = GetCameraToNDCTransform();
    helper_set_ndc(cameraToNDC, frameOfReference, displaySize);
}

void CameraView::SetViewSize(int new_pixel_width, int new_pixel_height) noexcept
{
    displaySize.x = static_cast<float>(new_pixel_width);
    displaySize.y = static_cast<float>(new_pixel_height);
    cameraToNDC = GetCameraToNDCTransform();
    helper_set_ndc(cameraToNDC, frameOfReference, displaySize);
}

void CameraView::SetZoom(float new_zoom) noexcept
{
    zoom = new_zoom;
    cameraToNDC = GetCameraToNDCTransform();
    helper_set_ndc(cameraToNDC, frameOfReference, displaySize, zoom);
}

void CameraView::AddZoom(float new_zoom)
{
    zoom += new_zoom;
    if (zoom > 0.0f)
    {
        cameraToNDC = GetCameraToNDCTransform();
        helper_set_ndc(cameraToNDC, frameOfReference, displaySize, zoom);
    }
    if (zoom < 0.1f)
    {
        zoom = 0.1f;
    }
}

void CameraView::SetFrameOfReference(FrameOfReference frame_of_reference) noexcept
{
    frameOfReference = frame_of_reference;
    cameraToNDC = GetCameraToNDCTransform();
    helper_set_ndc(cameraToNDC, frameOfReference, displaySize);
}