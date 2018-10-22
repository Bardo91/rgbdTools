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


namespace rgbd{
    template<typename PointType_>
    inline ClusterFrames<PointType_>::ClusterFrames(std::shared_ptr<DataFrame<PointType_>> &_df, int _id){
        id = _id;
        frames.push_back(_df->id);

        // Add df feature descriptors to cluster
        featureDescriptors = _df->featureDescriptors.clone();
        featureProjections.insert(featureProjections.end(), _df->featureProjections.begin(), _df->featureProjections.end());
        
        pose = _df->pose;
        position = _df->position;
        orientation = _df->orientation;
        cloud = _df->cloud;
        featureCloud = _df->featureCloud;

        intrinsic = _df->intrinsic;
        distCoeff = _df->coefficients;
        
        dataframes[_df->id] = _df;
        bestDataframe = _df->id;
        firstDataframe = _df;
        
        left = _df->left;   // TODO: Transition from dataframe
    }

    template<typename PointType_>
    inline void ClusterFrames<PointType_>::addDataframe(std::shared_ptr<DataFrame<PointType_>> &_df){
        frames.push_back(_df->id);

        // // Append df feature projetions to cluster
        // featureProjections.insert(featureProjections.end(), _df->featureProjections.begin(), _df->featureProjections.end());
        // // Add df feature descriptors to cluster
        // featureDescriptors.push_back(_df->featureDescriptors);
        dataframes[_df->id] = _df;
    }

    template<typename PointType_>
    inline void ClusterFrames<PointType_>::updateCovisibility(int _clusterId){
        if(std::find(covisibility.begin(), covisibility.end(), _clusterId) == covisibility.end()){
                        covisibility.push_back(_clusterId);
        }
        // covisibility.push_back(_clusterId)
    }

    template<typename PointType_>
    inline void ClusterFrames<PointType_>::addWord(std::shared_ptr<Word<PointType_>> &_word){
        wordsReference[_word->id] = _word;
    }

    template<typename PointType_>
    inline void ClusterFrames<PointType_>::switchBestDataframe(){
        int maxCounter = 0;
        int maxId = frames[0]; // start with first ID
        for(auto  &df: dataframes){
            int wordsCounter = 0;
            for(auto  &word: df.second->wordsReference){
                if(word->clusters.size() > 1){  // Word appears in at least 2 clusterframes
                    wordsCounter++;
                }
            }
            if(wordsCounter > maxCounter){
                maxCounter = wordsCounter;
                maxId = df.second->id;
            }
        }
        bestDataframe = maxId;
        std::cout << "Best dataframe in cluster " << id << " is " << bestDataframe << std::endl;
    }

    template<typename PointType_>
    inline void ClusterFrames<PointType_>::updatePose(Eigen::Matrix4f &_pose){
            pose          = _pose;
            position      = _pose.block<3,1>(0,3);
            orientation   = Eigen::Quaternionf(_pose.block<3,3>(0,0));
        }
}