#ifndef USER_CONFIG_HPP
#define USER_CONFIG_HPP

#include <boost/stacktrace/stacktrace_fwd.hpp>

#include <iosfwd>

namespace boost
{
	namespace stacktrace 
	{
		template <class CharT, class TraitsT, class Allocator>
		std::basic_ostream<CharT, TraitsT>& do_stream_st(std::basic_ostream<CharT, TraitsT>& os, const basic_stacktrace<Allocator>& bt) {
			const std::streamsize w = os.width();
			const std::size_t frames = bt.size();
			for (std::size_t i = 0; i < frames; ++i) {
				std::string sourceFile = bt[i].source_file();
				std::size_t indexOfFirstFolder = sourceFile.rfind('\\', sourceFile.rfind('\\') - 1);
				if (indexOfFirstFolder != std::string::npos ) sourceFile.erase(0, indexOfFirstFolder);
				
				
				os.width(2);
				os << i;
				os.width(w);
				os << "# ";
				os << bt[i].name();
				os << " at ";
				os << bt[i].source_line();
				os << "	    file ";
				os << sourceFile;
				os << '\n';
			}

			return os;
		}

		template <class CharT, class TraitsT>
		std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& os, const stacktrace& bt) {
			return do_stream_st(os, bt);
		}

	}
}  // namespace boost::stacktrace
#endif // USER_CONFIG_HPP