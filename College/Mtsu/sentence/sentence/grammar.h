#ifndef _GRAMMAR__H_
#define _GRAMMAR__H_

#include <string>

/*	The grammer of generating a sentence
	mission:
			Our_job_is_to " " do_goals "." |
			Our_job_is_to " " do_goals " " because "."

	Our_job_is_to:
			("It is our " | "It's our ") job " to" |
			"Our " job (" is to" | " is to continue to") |
			"The customer can count on us to" |
			("We continually " | "We ") ("strive" | "envision" | "exist") " to" |
			"We have committed to" |
			"We"
	job:
			"business" | "challenge" | "goal" | "job" | "mission" | "responsibility"

	do_goals:
			goal | goal " " in_order_to " " goal

	in_order_to:
			"as well as to" |
			"in order that we may" |
			"in order to" |
			"so that we may endeavor to" |
			"so that we may" |
			"such that we may continue to" |
			"to allow us to" |
			"while continuing to" |
			"and"

	because:
			"because that is what the customer expects" |
			"for 100% customer satisfaction" |
			"in order to solve business problems" |
			"to exceed customer expectations" |
			"to meet our customer's needs" |
			"to set us apart from the competition" |
			"to stay competitive in tomorrow's world" |
			"while promoting personal employee growth"

	goal: adverbly " " verb " " adjective " " noun

	adverbly:
			"quickly" | "proactively" | "efficiently" | "assertively" |
			"interactively" | "professionally" | "authoritatively" |
			"conveniently" | "completely" | "continually" | "dramatically" |
			"enthusiastically" | "collaboratively" | "synergistically" |
			"seamlessly" | "competently" | "globally"
    

	verb:
			"maintain" | "supply" | "provide access to" | "disseminate" |
			"network" | "create" | "engineer" | "integrate" | "leverage other's" |
			"leverage existing" | "coordinate" | "administrate" | "initiate" |
			"facilitate" | "promote" | "restore" | "fashion" | "revolutionize" |
			"build" | "enhance" | "simplify" | "pursue" | "utilize" | "foster" |
			"customize" | "negotiate"

	adjective:
			"professional" | "timely" | "effective" | "unique" | "cost-effective" |
			"virtual" | "scalable" | "economically sound" |
			"inexpensive" | "value-added" | "business" | "quality" | "diverse" |
			"high-quality" | "competitive" | "excellent" | "innovative" |
			"corporate" | "high standards in" | "world-class" | "error-free" |
			"performance-based" | "multimedia-based" | "market-driven" |
			"cutting edge" | "high-payoff" | "low-risk high-yield" |
			"long-term high-impact" | "prospective" | "progressive" | "ethical" |
			"enterprise-wide" | "principle-centered" | "mission-critical" |
			"parallel" | "interdependent" | "emerging" |
			"seven-habits-conforming" | "resource-leveling"
    
	noun:
			"content" | "paradigms" | "data" | "opportunities" |
			"information" | "services" | "materials" | "technology" | "benefits" |
			"solutions" | "infrastructures" | "products" | "deliverables" |
			"catalysts for change" | "resources" | "methods of empowerment" |
			"sources" | "leadership skills" | "meta-services" | "intellectual capital"
*/

	// Define category names as constants
	const std::string	MISSION_TOKEN = "<mission>";
	const std::string	OURJOB_TOKEN = "<Our_job_is_to>";
	const std::string	JOB_TOKEN = "<job>";
	const std::string	DOGOALS_TOKEN = "<do_goals>";
	const std::string	INORDERTO_TOKEN = "<in_order_to>";
	const std::string	BECAUSE_TOKEN = "<because>";
	const std::string	GOAL_TOKEN = "<goal>";
	const std::string	ADV_TOKEN = "<adverbly>";
	const std::string	VERB_TOKEN = "<verb>";
	const std::string	ADJ_TOKEN = "<adjective>";
	const std::string	NOUN_TOKEN = "<noun>";

	// The total number of rules in this grammar, i.e. the number of rows
	// in the array GRAMMAR
	const int		TOTAL_RULE_NUM = 128;

	// The column index for the array GRAMMAR
	enum ColumnIndex {CATEGORY=0, RULE};

	// This array contains the definition of the grammar, which is used
	// to generate a mission statement randomly.
	const std::string	GRAMMAR[][2] = {
			{MISSION_TOKEN, OURJOB_TOKEN + " " + DOGOALS_TOKEN + " ."},
			{MISSION_TOKEN, OURJOB_TOKEN + " " + DOGOALS_TOKEN + " " + BECAUSE_TOKEN + " ."},
			{OURJOB_TOKEN, "It is our " + JOB_TOKEN + " to"},
			{OURJOB_TOKEN, "Our " + JOB_TOKEN + " is to"},
			{OURJOB_TOKEN, "The customer can count on us to"},
			{OURJOB_TOKEN, "We have committed to"},
			{JOB_TOKEN, "business"},
			{JOB_TOKEN, "challenge"},
			{JOB_TOKEN, "goal"},
			{JOB_TOKEN, "job"},
			{JOB_TOKEN, "mission"},
			{JOB_TOKEN, "responsibility"},
			{DOGOALS_TOKEN, GOAL_TOKEN},
			{DOGOALS_TOKEN, GOAL_TOKEN + " " + INORDERTO_TOKEN + " " + GOAL_TOKEN},
			{INORDERTO_TOKEN, "as well as to"},
			{INORDERTO_TOKEN, "in order that we may"},
			{INORDERTO_TOKEN, "in order to"},
			{INORDERTO_TOKEN, "so that we may endeavor to"},
			{INORDERTO_TOKEN, "so that we may"},
			{INORDERTO_TOKEN, "such that we may continue to"},
			{INORDERTO_TOKEN, "to allow us to"},
			{INORDERTO_TOKEN, "while continuing to"},
			{INORDERTO_TOKEN, "and"},
			{BECAUSE_TOKEN, "because that is what the customer expects"},
			{BECAUSE_TOKEN, "for 100% customer satisfaction"},
			{BECAUSE_TOKEN, "in order to solve business problems"},
			{BECAUSE_TOKEN, "to exceed customer expectations"},
			{BECAUSE_TOKEN, "to meet our customer's needs"},
			{BECAUSE_TOKEN, "to set us apart from the competition"},
			{BECAUSE_TOKEN, "to stay competitive in tomorrow's world"},
			{BECAUSE_TOKEN, "while promoting personal employee growth"},
			{GOAL_TOKEN, ADV_TOKEN + " " + VERB_TOKEN + " " + ADJ_TOKEN + " " + NOUN_TOKEN},
			{ADV_TOKEN, "quickly"},
			{ADV_TOKEN, "proactively"},
			{ADV_TOKEN, "efficiently"},
			{ADV_TOKEN, "assertively"},
			{ADV_TOKEN, "interactively"},
			{ADV_TOKEN, "professionally"},
			{ADV_TOKEN, "authoritatively"},
			{ADV_TOKEN, "conveniently"},
			{ADV_TOKEN, "completely"},
			{ADV_TOKEN, "continually"},
			{ADV_TOKEN, "dramatically"},
			{ADV_TOKEN, "enthusiastically"},
			{ADV_TOKEN, "collaboratively"},
			{ADV_TOKEN, "synergistically"},
			{ADV_TOKEN, "seamlessly"},
			{ADV_TOKEN, "competently"},
			{ADV_TOKEN, "globally"},
			{VERB_TOKEN, "maintain"},
			{VERB_TOKEN, "supply"},
			{VERB_TOKEN, "provide access to" }, 
			{VERB_TOKEN, "disseminate" },
			{VERB_TOKEN, "network" }, 
			{VERB_TOKEN, "create" }, 
			{VERB_TOKEN, "engineer" }, 
			{VERB_TOKEN, "integrate" }, 
			{VERB_TOKEN, "leverage other's" },
			{VERB_TOKEN, "leverage existing" }, 
			{VERB_TOKEN, "coordinate" }, 
			{VERB_TOKEN, "administrate" }, 
			{VERB_TOKEN, "initiate" },
			{VERB_TOKEN, "facilitate" },
			{VERB_TOKEN, "promote" }, 
			{VERB_TOKEN, "restore" },
			{VERB_TOKEN, "fashion" },
			{VERB_TOKEN, "revolutionize" },
			{VERB_TOKEN, "build" }, 
			{VERB_TOKEN, "enhance" },
			{ADJ_TOKEN, "professional" },
			{ADJ_TOKEN, "timely" },
			{ADJ_TOKEN, "effective" },
			{ADJ_TOKEN, "unique" },
			{ADJ_TOKEN, "cost-effective" },
			{ADJ_TOKEN, "virtual" },
			{ADJ_TOKEN, "scalable" },
			{ADJ_TOKEN, "economically sound" },
			{ADJ_TOKEN, "inexpensive" },
			{ADJ_TOKEN, "value-added" },
			{ADJ_TOKEN, "business" },
			{ADJ_TOKEN, "quality" },
			{ADJ_TOKEN, "diverse" },
			{ADJ_TOKEN, "high-quality" },
			{ADJ_TOKEN, "competitive" },
			{ADJ_TOKEN, "excellent" },
			{ADJ_TOKEN, "innovative" },
			{ADJ_TOKEN, "corporate" },
			{ADJ_TOKEN, "high standards in" },
			{ADJ_TOKEN, "world-class" },
			{ADJ_TOKEN, "error-free" },
			{ADJ_TOKEN, "performance-based" },
			{ADJ_TOKEN, "multimedia-based" },
			{ADJ_TOKEN, "market-driven" },
			{ADJ_TOKEN, "cutting edge" },
			{ADJ_TOKEN, "high-payoff" },
			{ADJ_TOKEN, "low-risk high-yield" },
			{ADJ_TOKEN, "long-term high-impact" },
			{ADJ_TOKEN, "prospective" },
			{ADJ_TOKEN, "progressive" },
			{ADJ_TOKEN, "ethical" },
			{ADJ_TOKEN, "enterprise-wide" },
			{ADJ_TOKEN, "principle-centered" },
			{ADJ_TOKEN, "mission-critical" },
			{ADJ_TOKEN, "parallel" },
			{ADJ_TOKEN, "interdependent" },
			{ADJ_TOKEN, "emerging" },
			{ADJ_TOKEN, "seven-habits-conforming" },
			{ADJ_TOKEN, "resource-leveling"},
			{NOUN_TOKEN, "content" },
			{NOUN_TOKEN, "paradigms" },
			{NOUN_TOKEN, "data" },
			{NOUN_TOKEN, "opportunities" },
			{NOUN_TOKEN, "information" },
			{NOUN_TOKEN, "services" },
			{NOUN_TOKEN, "materials" },
			{NOUN_TOKEN, "technology" },
			{NOUN_TOKEN, "benefits" },
			{NOUN_TOKEN, "solutions" },
			{NOUN_TOKEN, "infrastructures" },
			{NOUN_TOKEN, "products" },
			{NOUN_TOKEN, "deliverables" },
			{NOUN_TOKEN, "catalysts for change" },
			{NOUN_TOKEN, "resources" },
			{NOUN_TOKEN, "methods of empowerment" },
			{NOUN_TOKEN, "sources" },
			{NOUN_TOKEN, "leadership skills" },
			{NOUN_TOKEN, "meta-services" },
			{NOUN_TOKEN, "intellectual capital"}};

#endif

