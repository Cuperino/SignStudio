#ifndef SIGNVEC_H
#define SIGNVEC_H

#include "qlist.h"

enum Handedness {
    RightHand = false,
    LeftHand = true
};

enum Interpolation {
    Linear,
    Ease,
    EaseIn,
    EaseOut
};

enum WristRotationMode {
    Point,          // Wrist rests while hand points to destination.
    Parallel,       // Hand absolute rotation remains constant between source and destination.
    FollowMotion    // Wrist rotates with angles perpendicular to the motion.
};

// Animations that take place while at the keyframe's timestamp
enum AnimationModifiers {
    Still           = 0,
    // Animations
    Lateral         = 0b0 << 1,
    Circle          = 0b1 << 1,
    // Animations
    Transitive      = 0b0 << 1,
    Rotative        = 0b1 << 1,
    //
    PointOscillateZ = 0b001 << 2,
    Rub             = 0b010 << 2,
    PointCircle     = 0b011 << 2,
    Encircle        = 0b100 << 2
};

enum Directionality {
    // Y-Angles
    Front           = 0b0 << 0,
    Back            = 0b1 << 0,
    YForward        = 0b000 << 1,
    YDeg30          = 0b001 << 1,
    YDeg45          = 0b010 << 1,
    YDeg60          = 0b011 << 1,
    YDeg90          = 0b100 << 1
};

enum ReferenceObjects {
    // I'm attempting to have all encodable positions fit in 2 bytes, to optimize for performance on 32 bit WASM and optimize ML encodings.
    Neutral         = 0,

    // Flags (8 of 8 bits, mostly used)
    // Person
    Self            = 0b0 << 0,
    SecondPerson    = 0b1 << 0,  // Default behavior equals to Deg45

    // Shift/Mirror part with its other side counterpart
    NoShift         = 0b0 << 1,  // M
    Shift           = 0b1 << 1,  // M
    // X-Offset from center to handedness by around 2 centimeters
    NoOffset        = 0b0 << 1,  // U
    SmallOffset     = 0b1 << 1,  // U

    // Sides
    Unspecified     = 0b000 << 2,
    FrontLateral    = 0b001 << 2,
    BackLateral     = 0b010 << 2,
    LeftLateral     = 0b011 << 2,
    ThumbLateral    = ReferenceObjects::LeftLateral,
    RightLateral    = 0b100 << 2,
    PinkyLateral    = ReferenceObjects::RightLateral,
    TopLateral      = 0b101 << 2,
    BottomLateral   = 0b110 << 2,
    // Unused bit combination: 0b111 << 2.

    // Z-Depths
    Body            = 0b000 << 5, // Pont to object
    SignSpace       = 0b001 << 5, // XY on object, but Z about a feet in front of object
    Ahead           = 0b010 << 5, // XY on object, but Z ahead of object
    AheadExtended   = 0b011 << 5, // XY on object, but arm fully extended
    Behind          = 0b100 << 5, // XY on object, but Z behind object

    // FingerModifiers
    InnerJoint      = 0b100 << 5, // Intentional collision. Using free space from Z-Depths to save 2 extra flag bits
    MiddleJoint     = 0b101 << 5,
    OuterJoint      = 0b110 << 5,
    NailJoint       = 0b111 << 5,

    // Objects (6 of 8 bits used)
    // M: mirrorable, U: unmirrorable
    GlobalCenter    = 1 << 8,  // U
    OthersHand      = 2 << 8,  // M
    Camera          = 3 << 8,  // U
    Ceiling         = 4 << 8,  // M
    OverHead        = 5 << 8,  // U
    Head            = 6 << 8,  // M
    HeadTop         = ReferenceObjects::Head & ReferenceObjects::TopLateral,  // U
    Hair            = 7 << 8,  // M
    Face            = 8 << 8,  // M
    Forehead        = 9 << 8,  // U
    ForeheadAboveEyebrow = 10 << 8,  // M
    Glabella        = 11 << 8,  // U
    Eyebrow         = 12 << 8,  // M
    Eye             = 13 << 8,  // M
    Temple          = 14 << 8,  // M   // Sien
    Ear             = 15 << 8,  // M
    NoseTip         = 16 << 8,  // U
    CheekBone       = 17 << 8,  // M
    Stashe          = 18 << 8,  // U
    MouthTip        = 19 << 8,  // U
    UpperLip        = 20 << 8,  // U
    Tounge          = 21 << 8,  // U
    LowerLip        = 22 << 8,  // U
    MouthCorner     = 23 << 8,  // M
    Cheeck          = 24 << 8,  // M
    ChinTip         = 25 << 8,  // U
    Jaw             = 26 << 8,  // M
    HeadBottom      = ReferenceObjects::Face & ReferenceObjects::BottomLateral,  // U  // Papada
    Thyroid         = 27 << 8,  // U
    Thrachea        = 28 << 8,  // U
    Clavicule       = 29 << 8,  // U
    Shoulder        = 30 << 8,  // M
    UpperArm        = 31 << 8,  // M
    Elbow           = 32 << 8,  // M
    Forearm         = 33 << 8,  // M
    Wrist           = 34 << 8,  // M
    PinkyFinger     = 35 << 8,  // M
    RingFinger      = 36 << 8,  // M
    MiddleFinger    = 37 << 8,  // M
    IndexFinger     = 38 << 8,  // M
    ThumbFinger     = 39 << 8,  // M
    Chest           = 40 << 8,  // M
    Heart           = 41 << 8,  // M  // Heart should be mirrorable
    Sternum         = 42 << 8,  // U
    Ribs            = 43 << 8,  // M
    BellyButton     = 44 << 8,  // U
    Belly           = 45 << 8,  // M
    Hip             = 46 << 8,  // M
    BeltBuckle      = 47 << 8,  // M
    Belt            = 48 << 8,  // M
    Crotch          = 49 << 8,  // U
    Gluteus         = 50 << 8,  // U
    Tight           = 51 << 8,  // M
    Knee            = 52 << 8,  // M
    Calf            = 53 << 8,  // M   // Pantorrilla
    Ankle           = 54 << 8,  // M
    Feet            = 55 << 8,  // M
    Toe             = 56 << 8,  // M
    Floor           = 57 << 8,  // M
    RingMain        = 58 << 8,  // M
    RingFirst       = 59 << 8,  // M
    RingLast        = 60 << 8   // M
};

// Physics

struct Position
{
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Normal : public Position
{
    double rotX = 0;
    double rotZ = 0;
};

struct Rectangle : public Normal
{
    double width = 1;
    double height = 1;
};

struct Cuboid : public Rectangle
{
    double depth = 0;
};

// Database

struct ReferenceObject : public Cuboid
{
    ReferenceObjects object = ReferenceObjects::Neutral;
};

// Keyframes
// Keyframes store timestamp, value and intempolation

// Virtual keyframe holds no value
struct KeyFrame
{
    long timestamp = 0;
    Interpolation positionInterpolation = Interpolation::Linear;
};

// Value Keyframe stores one numeric value of any type.
template <typename MagnitudeType>
struct ValueKeyFrame : public KeyFrame
{
    MagnitudeType value;
};

// Stores XYZ coordinates on a single keyframe.
struct PositionKeyFrame : public KeyFrame, public Position
{};

struct WristKeyFrame : public KeyFrame
{
    WristRotationMode mode = WristRotationMode::Point;
    AnimationModifiers animation_modifier = AnimationModifiers::Still;
    ReferenceObject reference;
    int distance = 0;
};

class SignVec
{
public:
    SignVec();
private:
    QList<ReferenceObject> reference_objects;
    QList<WristKeyFrame> left_hand;
    QList<WristKeyFrame> right_hand;
};

#endif // SIGNVEC_H
