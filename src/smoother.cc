#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

// http://bitsquid.blogspot.se/2010/10/time-step-smoothing.html

template<typename REAL>
class Smoother {
public:
	typedef size_t INDEX;
	static const INDEX SIZE = 11;

	Smoother() {
	}

	void AddData(REAL data) {
		if (data_.size() + 1 > SIZE) data_.erase(data_.begin());
		data_.push_back(data);
	}

	template<typename DELTA>
	REAL GetSmoothed(DELTA p) const {
		assert(0 <= p && p <= 1);
		const size_t total_count = data_.size();
		if (total_count == 0) return static_cast<REAL>(0);
		const REAL last = *data_.rbegin();
		if (total_count == 1) return last;
		std::vector<REAL> data = data_;
		if (total_count > 5) {
			std::sort(data.begin(), data.end());
			data.erase(data.begin());
			data.erase(data.begin());
			data.erase(--data.end());
			data.erase(--data.end());
		}
		const REAL mean = std::accumulate(data.begin(), data.end(), static_cast<REAL>(0));
		const REAL smoothed = p*mean + (1 - p)*last;
		return smoothed;
	}
private:
	std::vector<REAL> data_;
};

void smoother_test() {
	Smoother<float> smoother;
	float data = smoother.GetSmoothed(0.1f);
	smoother.AddData(1.0f);
	smoother.AddData(2.0f);
	smoother.AddData(4.0f);
	smoother.AddData(55.0f);
	smoother.AddData(1.0f);
	float beta = smoother.GetSmoothed(0.1f);
	smoother.AddData(2.0f);
	smoother.AddData(4.0f);
	smoother.AddData(55.0f);
	smoother.AddData(1.0f);
	smoother.AddData(2.0f);
	smoother.AddData(4.0f);
	smoother.AddData(55.0f);
	float smoothed = smoother.GetSmoothed(0.1f);
}


