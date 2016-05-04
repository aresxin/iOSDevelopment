#ifndef ANNOTATION_EMF_CREATOR_H
#define ANNOTATION_EMF_CREATOR_H

struct AnnotationParameter;

class AnnotationEMFCreator
{
public:
	enum {
		no_error = 0,
		error_invalid_arg = 0x80070057,
		error_outofmemory = 0x8007000E,
	};

	class EMF {
	public:
		EMF();
		~EMF();
		void SetData(const unsigned char* data, size_t size);
		unsigned char* GetData() const { return m_data; }
		size_t GetSize() const { return m_size; }
	private:
		unsigned char* m_data;
		size_t m_size;
	};

public:
	AnnotationEMFCreator();
	AnnotationEMFCreator(int resolution);
	~AnnotationEMFCreator();
	int CreateEMFData(AnnotationParameter& param, EMF& emf) const;

private:
	int m_resolution;
};

#endif
