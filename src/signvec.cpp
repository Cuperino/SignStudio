// SPDX-FileCopyrightText: 2022 Javier O. Cordero Pérez
//
// SPDX-License-Identifier: AGPL-3.0-only

#include "signvec.h"

SignVec::SignVec()
{
    // Parse database file


    // Initialize object database
    this->reference_objects.append(
        ReferenceObject {
            0,  // x
            11, // y
            0,  // z
            0,  // rotX
            0,  // rotZ
            2,  // width
            2,  // height
            2,  // depth
            ReferenceObjects::Forehead
        });
    this->reference_objects.append(
        ReferenceObject {
            0,  // x
            5,  // y
            2,  // z
            0,  // rotX
            0,  // rotZ
            4,  // width
            2,  // height
            3,  // depth
            ReferenceObjects::Belly
        });

    // Test data

    // Add keyframes
    this->right_hand.append(
        WristKeyFrame {
            0,                                  // timestamp
            Interpolation::Linear,              // Interpolation
            WristRotationMode::FollowMotion,    // rotation mode
            AnimationModifiers::Still,
            this->reference_objects.first(),    // ReferenceObject
            0                                   // distance
        });
    this->right_hand.append(
        WristKeyFrame {
            200,                                // timestamp
            Interpolation::Linear,              // Interpolation
            WristRotationMode::FollowMotion,    // rotation mode
            AnimationModifiers::Still,
            this->reference_objects.last(),     // ReferenceObject
            0                                   // distance
        });

}
