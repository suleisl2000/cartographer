
#ifndef CARTOGRAPHER_SENSOR_RANGE_DATA_H_
#define CARTOGRAPHER_SENSOR_RANGE_DATA_H_

#include "cartographer/common/port.h"
#include "cartographer/sensor/compressed_point_cloud.h"
#include "cartographer/sensor/point_cloud.h"
#include "cartographer/sensor/proto/sensor.pb.h"

namespace cartographer {
namespace sensor {

/*
RangeData:
数据成员包括 原始位置,返回点云光线,缺失点云光线
*/
// Rays begin at 'origin'. 'returns' are the points where obstructions were
// detected. 'misses' are points in the direction of rays for which no return
// was detected, and were inserted at a configured distance. It is assumed that
// between the 'origin' and 'misses' is free space.
struct RangeData {
  Eigen::Vector3f origin;//{x,y,z}
  PointCloud returns;
  PointCloud misses;
};

// Converts 'range_data' to a proto::RangeData. 序列化
proto::RangeData ToProto(const RangeData& range_data);

// Converts 'proto' to a RangeData. 反序列化
RangeData FromProto(const proto::RangeData& proto);

//对数据进行变换
RangeData TransformRangeData(const RangeData& range_data,
                             const transform::Rigid3f& transform);

//剪裁到给定范围
// Crops 'range_data' according to the region defined by 'min_z' and 'max_z'.
RangeData CropRangeData(const RangeData& range_data, float min_z, float max_z);

//压缩后的点云数据
// Like RangeData but with compressed point clouds. The point order changes
// when converting from RangeData.
struct CompressedRangeData {
  Eigen::Vector3f origin;
  CompressedPointCloud returns;
  CompressedPointCloud misses;
};

CompressedRangeData Compress(const RangeData& range_data);

RangeData Decompress(const CompressedRangeData& compressed_range_Data);

}  // namespace sensor
}  // namespace cartographer

#endif  // CARTOGRAPHER_SENSOR_RANGE_DATA_H_