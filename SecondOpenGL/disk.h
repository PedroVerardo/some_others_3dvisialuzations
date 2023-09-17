#include <memory>
class Disk;
using DiskPtr = std::shared_ptr<Disk>;

#ifndef DISK_H
#define DISK_H

#include "shape.h"

class Disk : public Shape {
	unsigned int m_vao;
protected:
	Disk();
public:
	static DiskPtr Make();
	virtual ~Disk();
	virtual void Draw(StatePtr st);
};
#endif