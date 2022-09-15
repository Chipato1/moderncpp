class CmdLineOptParser
{
public:
	virtual ~CmdLineOptParser() = default;
	bool Parse(int argc, char* argv[]);

protected:
	virtual bool Option(const char c, const char* info);
};