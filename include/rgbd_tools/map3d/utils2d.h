//---------------------------------------------------------------------------------------------------------------------
//  RGBD_TOOLS
//---------------------------------------------------------------------------------------------------------------------
//  Copyright 2018 Pablo Ramon Soria (a.k.a. Bardo91) pabramsor@gmail.com
//---------------------------------------------------------------------------------------------------------------------
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
//  and associated documentation files (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge, publish, distribute,
//  sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial
//  portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
//  OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//---------------------------------------------------------------------------------------------------------------------


#ifndef RGBDTOOLS_MAP3D_UTILS2D_H_
#define RGBDTOOLS_MAP3D_UTILS2D_H_

#include <opencv2/opencv.hpp>
#include <vector>

namespace rgbd{

    /// Perform alignment between two clouds using RANSAC
    /// \param _des1:
    /// \param _des2:
    /// \param _inliers:
    /// \param _mk_nearest_neighbors:
    /// \param _mFactorDescriptorDistance:
    bool matchDescriptors(const cv::Mat &_des1,
			  const cv::Mat &_des2, 
			  std::vector<cv::DMatch> &_inliers,
			  double _mk_nearest_neighbors,
			  double _mFactorDescriptorDistance);

}

#include "utils2d.inl"

#endif
