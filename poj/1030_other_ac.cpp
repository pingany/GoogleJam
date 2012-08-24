#include <iostream>
using namespace std;

enum Status
{
	UNCERTAIN = 0,
	INSINGLE,
	INBOTH
};

enum JoinType
{
	NONE = 0,
	FIRST,
	SECOND,
	BOTH
};

struct TeamRecord
{
	int rank1;
	int rank2;
	int sumRanks;
	JoinType joinType;
};

struct LinkTeamRecord
{
	int teamId;
	LinkTeamRecord *right;
	LinkTeamRecord *next;
	LinkTeamRecord(int _teamId): right(NULL),next(NULL)
	{
		teamId = _teamId;
	}
	~LinkTeamRecord()
	{
		if(right) delete right;
		if(next) delete next;
	}
};

//globals///
const int TEAMSCOUNT = 100;
const char *DELIMITERS = " \n";
char LINEDATA[3*TEAMSCOUNT];
TeamRecord g_teamRecords[TEAMSCOUNT+1];
int g_contestRanks[4*TEAMSCOUNT+2];
////////////

class ContestInfoReader
{
public:
	ContestInfoReader()
	{
		memset(g_teamRecords, 0, sizeof(g_teamRecords));
		memset(g_contestRanks, 0, sizeof(g_contestRanks));
	}
	void InitData()
	{
		m_currentRankIndex = 0;
		m_currentContestNumber = 1;
		ReadContestData();

		gets(LINEDATA);

		FillContestRank(0);
		m_currentContestNumber = 2;
		ReadContestData();
		FillContestRank(0);
	}
	bool NextTeamOfBothType()
	{
		++m_currentTeamId;
		for(int i=m_currentTeamId; i<=TEAMSCOUNT; ++i)
			if(g_teamRecords[i].joinType == BOTH)
			{
				m_currentTeamId = i;
				return true;
			};
		return false;
	}
	bool NextTeamOfSingleType()
	{	
		int teamIndex = g_contestRanks[++m_currentRankIndex];
		while(teamIndex != 0)
		{
			JoinType type = (m_currentContestNumber==1)?FIRST:SECOND;
			if(g_teamRecords[teamIndex].joinType != type)
				teamIndex = g_contestRanks[++m_currentRankIndex];
			else
			{
				m_currentTeamId = teamIndex;
				return true;
			}				
		}
	
		if(PrepareForNextGroup())
			return NextTeamOfSingleType();
		else
			return false;	
	}
	void ResetCurrentTeamId()
	{
		m_currentTeamId = 0;
	}
	void ResetCurrentRank()
	{
		m_currentRankIndex = -1;
		m_currentContestNumber = 1;
		PrepareForNextGroup();
	}

	int CurrentTeamId()
	{
		return m_currentTeamId;
	}
	Status& CurrentStatus()
	{
		return m_status;
	}
	int CurrentGroupId()
	{
		return m_groupIndex;
	}
protected:
	void ReadContestData()
	{
		int rankSum, rankCur; 
		int teamId, teamCount;
		char *pCur;

		gets(LINEDATA);
		sscanf(LINEDATA, "%d", &teamCount);

		rankSum = 0;
		for(int i=0; i<teamCount; ++i)
		{
			gets(LINEDATA);
			rankCur = rankSum+1;
			pCur = strtok(LINEDATA, DELIMITERS);
			while(pCur)
			{
				++rankSum;
				teamId = atoi(pCur);
				FillTeamRecord(teamId, rankCur);
				FillContestRank(teamId);
				pCur = strtok(NULL, DELIMITERS);
			}
			FillContestRank(0);
		}
	}
	void FillTeamRecord(int teamId, int rank)
	{
		if(m_currentContestNumber == 1)
		{
			g_teamRecords[teamId].joinType = FIRST;
			g_teamRecords[teamId].rank1 = rank;
		}
		else if(m_currentContestNumber == 2)
		{
			if(g_teamRecords[teamId].joinType == NONE)
			{
				g_teamRecords[teamId].joinType = SECOND;
				g_teamRecords[teamId].rank2 = rank;
			}
			else if(g_teamRecords[teamId].joinType == FIRST)
			{
				int rank1 = g_teamRecords[teamId].rank1;
				g_teamRecords[teamId].joinType = BOTH;
				g_teamRecords[teamId].rank2 = rank;
				g_teamRecords[teamId].sumRanks = rank1+rank;
			}
		}
	}
	void FillContestRank(int teamId)
	{
		g_contestRanks[m_currentRankIndex++] = teamId;
	}
	bool PrepareForNextGroup()
	{
		int rankIndex = m_currentRankIndex+1;
		if(g_contestRanks[rankIndex] > 0)
		{
			SetGroupStatus();
			if(m_status == UNCERTAIN)
			{
				JumpCurrentGroup();
				return PrepareForNextGroup();
			}
			return true;
		}
		else if(m_currentContestNumber == 1)
		{
			++m_currentRankIndex;
			m_currentContestNumber = 2;
			return PrepareForNextGroup();
		}
		return false;
	}
	void SetGroupStatus()
	{
		m_groupIndex = 0;
		bool bUncertain = false;
		for(int i=m_currentRankIndex+1; ;++i)
		{
			int teamIndex = g_contestRanks[i];
			if(teamIndex == 0)
				break;

			if(g_teamRecords[teamIndex].joinType == BOTH)
			{
				if(m_groupIndex == 0)
					m_groupIndex = teamIndex;
				else if(g_teamRecords[m_groupIndex].sumRanks != g_teamRecords[teamIndex].sumRanks)
				{
					bUncertain = true;
					break;
				}
			}
		}

		if(bUncertain)
			m_status = UNCERTAIN;
		else if(m_groupIndex == 0)
			m_status = INSINGLE;
		else
		    m_status = INBOTH;
	}
	void JumpCurrentGroup()
	{
		int teamIndex = g_contestRanks[++m_currentRankIndex];
		while(teamIndex != 0)
			teamIndex = g_contestRanks[++m_currentRankIndex];
	}
private:
	//for iteration
	int m_currentTeamId;
	int m_currentRankIndex;
	int m_currentContestNumber;

	//group status
        Status m_status;
	int m_groupIndex;
};

class ContestRatingSorter
{
public:
	ContestRatingSorter() : m_pHead(NULL)
	{}
	~ContestRatingSorter()
	{
		if(m_pHead)
			delete m_pHead;
	}

	bool PrepareForInsert(int id)
	{
		m_pInsert = new LinkTeamRecord(id);
		if(m_pHead)
		{
			ResetFromHead();
			return true;
		}
		m_pHead = m_pInsert;
		return false;		
	}
	void InsertBothType()
	{
		int sumInsert = g_teamRecords[m_pInsert->teamId].sumRanks;
		int sumCurrent = g_teamRecords[m_pHead->teamId].sumRanks;

		if(sumInsert > sumCurrent)
		{
			while(NextGroup())
			{
				sumCurrent = g_teamRecords[m_pCurrentGroup->teamId].sumRanks;
				if(sumInsert <= sumCurrent)
					break;
			}
		}
	
		if(sumInsert == sumCurrent)
			InsertInGroup();
		else 
			NewGroup();
	}
	void InsertSingleInBothType(int groupId)
	{
		Find(groupId);
		InsertInGroup();
	}
	bool InsertSingleType()
	{
		bool bUncertain = false;
		bool bFindGroup = false;
		LinkTeamRecord *pFront = NULL;
		LinkTeamRecord *pBack = NULL; 
		
		JoinType typeInsert = g_teamRecords[m_pInsert->teamId].joinType;
		int rankInsert = GetSingleRank(typeInsert, m_pInsert->teamId);
		
		do
		{
			int rankCurrent = GetSingleRank(typeInsert, m_pCurrentNode->teamId);
			if(rankCurrent != 0)
			{
				if(rankInsert > rankCurrent)
				{
					if(pBack)
					{
						bUncertain = true;
						break;
					}
					pFront = m_pCurrentGroup;
				}			
				else if(rankInsert < rankCurrent)
				{
					if(m_pCurrentGroup == pFront)
					{
						bUncertain = true;
						break;
					}
					if(!pBack)
						pBack = m_pCurrentGroup;
				}		
				else
				{
					bFindGroup = true;
					break;
				}
			}
		}
		while(Next());

		if(!bUncertain)
		{
			if(bFindGroup)
				InsertInGroup();
			else
				InsertBetweenGroups(pFront, pBack);
			return true;
		}
		
		if(m_pInsert)
			delete m_pInsert;  //free memory
		return false;
	}
	void PrintRatingList()
	{
		LinkTeamRecord *pGroup = m_pHead;
		LinkTeamRecord *pNode = m_pHead;
		while(pGroup)
		{
			printf("%d", pGroup->teamId);
			pNode = pGroup->right;
			while(pNode)
			{
				printf("%s%d"," ",pNode->teamId);
				pNode = pNode->right;
			}
			printf("\n");
			pGroup = pGroup->next;
		}
	}
protected:
	void ResetFromHead()
	{
		ResetFromGroup(NULL);
	}
	void ResetFromGroup(LinkTeamRecord *pPre)
	{
		LinkTeamRecord *pCur = NULL;
		if(!pPre)
			pCur = m_pHead;
		else
			pCur = pPre->next;

		m_pPreviousNode = NULL;
		m_pCurrentNode = pCur;
		m_pPreviousGroup = pPre;
		m_pCurrentGroup = pCur;
	}
	bool Next()
	{
		if(!NextNodeInGroup())
			return NextGroup();
		return true;
	}
	bool NextGroup()
	{
		m_pPreviousGroup = m_pCurrentGroup;
		m_pCurrentGroup = m_pCurrentGroup->next;
		m_pPreviousNode = NULL;
		m_pCurrentNode = m_pCurrentGroup;
		return m_pCurrentGroup!=NULL;
	}
	bool NextNodeInGroup()
	{
		m_pPreviousNode = m_pCurrentNode;
		m_pCurrentNode = m_pCurrentNode->right;
		return m_pCurrentNode!=NULL;
	}
	void InsertInGroup()
	{
		//restart from current group
		m_pPreviousNode = NULL;
		m_pCurrentNode = m_pCurrentGroup;

		int idInsert = m_pInsert->teamId;
		if(idInsert > m_pCurrentGroup->teamId)
		{
			while(NextNodeInGroup())
			{
				if(idInsert < m_pCurrentNode->teamId)
					break;
			}
		}	
		NewNode();
	}
	void InsertBetweenGroups(LinkTeamRecord *front, LinkTeamRecord *back)
	{
		ResetFromGroup(front);

		int rankCurrent = 0;
		int rankInsert = GetSingleRank(m_pInsert->teamId);
		
		while(m_pCurrentGroup != back)
		{
			rankCurrent = GetSingleRank(m_pCurrentGroup->teamId);
			if(rankInsert <= rankCurrent)
				break;
			NextGroup();
		}

		if(rankInsert == rankCurrent)
			InsertInGroup();
		else
			NewGroup();
	}
	void NewGroup()
	{
		if(m_pCurrentGroup == m_pHead)
		{
			//new head
			m_pInsert->next = m_pHead;
			m_pHead = m_pInsert;
		}
		else
		{
			//new group
			m_pPreviousGroup->next = m_pInsert;
			m_pInsert->next = m_pCurrentGroup;
		}
	}
	void NewNode()
	{
		if(m_pCurrentNode == m_pCurrentGroup)
		{
			if(m_pPreviousGroup)
				m_pPreviousGroup->next = m_pInsert;

			m_pInsert->right = m_pCurrentGroup;
			m_pInsert->next = m_pCurrentGroup->next;
			m_pCurrentGroup->next = NULL;

			//new head
			if(!m_pPreviousGroup)
				m_pHead = m_pInsert;
		}
		else
		{
			m_pPreviousNode->right = m_pInsert;
			m_pInsert->right = m_pCurrentNode;
		}
	}
	LinkTeamRecord *Find(int id)
	{
		if(id != m_pHead->teamId)
			while(Next())
			{
				if(id == m_pCurrentNode->teamId)
					break;
			};
		return m_pCurrentNode;
	}
	int GetSingleRank(int teamId)
	{
		int rank = 0;
		TeamRecord team = g_teamRecords[teamId];
		if(team.joinType == FIRST)
			rank = team.rank1;
		else if(team.joinType == SECOND)
			rank = team.rank2;
		return rank;
	}
	int GetSingleRank(JoinType type, int teamId)
	{
		int rank = 0;
		TeamRecord team = g_teamRecords[teamId];
		if(type == FIRST)
			rank = team.rank1;
		else if(type == SECOND)
			rank = team.rank2;
		return rank;
	}
private:
	LinkTeamRecord *m_pHead;
	LinkTeamRecord *m_pInsert;

	//for iteration
	LinkTeamRecord *m_pPreviousGroup;
	LinkTeamRecord *m_pCurrentGroup;
	LinkTeamRecord *m_pPreviousNode;
	LinkTeamRecord *m_pCurrentNode;
};
int main()
{
	ContestInfoReader reader;
	ContestRatingSorter sorter;
	
	reader.InitData();
	reader.ResetCurrentTeamId();
	while(reader.NextTeamOfBothType())
	{
		int id = reader.CurrentTeamId();
		if(sorter.PrepareForInsert(id))
			sorter.InsertBothType();
	}

	reader.ResetCurrentRank();
	while(reader.NextTeamOfSingleType())
	{
		int id = reader.CurrentTeamId();
		if(sorter.PrepareForInsert(id))
		{
			Status status = reader.CurrentStatus();
			if(status == INBOTH)
			{
				int groupId = reader.CurrentGroupId();
				sorter.InsertSingleInBothType(groupId);
			}
			else if(status == INSINGLE)
				sorter.InsertSingleType();
		}		
	}

	sorter.PrintRatingList();
	return 0;
}