#ifndef CONVERTER_HPP
# define CONVERTER_HPP

namespace aua
{
	class converter
	{
		protected:
			converter();
			~converter();
			converter(const converter &other);
		public:
			converter &operator=(const converter &other);

	};
} // namespace aua

#endif
