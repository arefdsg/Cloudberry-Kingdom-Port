#ifndef SCOREENTRY
#define SCOREENTRY

#include <global_header.h>

namespace CloudberryKingdom
{
	class ScoreEntry
	{
	public:
		enum Format
		{
			Format_SCORE,
			Format_LEVEL,
			Format_ATTEMPTS,
			Format_TIME
		};
	public:
		const static std::wstring getDefaultName();

		int GameId;
		int Value, Score, Level_Renamed, Attempts, Time, Date;
		std::wstring GamerTag_Renamed;
		bool Fake;

		ScoreEntry();

		ScoreEntry( int Score );

		ScoreEntry( std::wstring &GamerTag_Renamed, int Game, int Value, int Score, int Level_Renamed, int Attempts, int Time, int Date );

		void WriteChunk_1000( const std::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_1000( const std::shared_ptr<Chunk> &chunk );

		virtual std::wstring ToString();

		Format MyFormat;
		std::wstring _ToString();

		std::wstring _ToString( Format format );

	private:
		std::wstring ScoreToString();

		std::wstring TimeToString();

		std::wstring AttemptsToString();

		std::wstring LevelToString();

	public:
		std::wstring ToString( int Length );

		/// <summary>
		/// Returns a string of the form "{root}........{score}"
		/// </summary>
		/// <param name="Length">The desired length of the string</param>
		/// <param name="MinDots">The minimum number of dots seperating the root from the score</param>
		/// <returns></returns>
		static std::wstring DottedScore( std::wstring root, int score, int Length, int MinDots );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCOREENTRY
