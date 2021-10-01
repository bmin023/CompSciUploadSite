import { SunIcon, MoonIcon } from "@chakra-ui/icons";
import {
  Box,
  Button,
  Flex,
  Spacer,
  useColorMode,
  useDisclosure,
} from "@chakra-ui/react";
import axios from "axios";
import { GetServerSideProps, NextPage } from "next";
import PropTypes from "prop-types";
import React, { useState } from "react";

import AssignmentBox from "components/AssignmentBox";
import WarningModal from "components/WarningModal";
import { Assignment, CodeReturn, getAssignments } from "utils/assignmentUtils";
import { UploadPostRes } from "./api/uploads";

interface IProps {
  assignments: Assignment[];
}

const Home: NextPage<IProps> = ({ assignments }) => {
  const {
    isOpen: warningsOpen,
    onClose: onWarningsClose,
    onOpen: onWarningsOpen,
  } = useDisclosure();
  const [warnings, setWarnings] = useState([] as string[]);
  const { colorMode, toggleColorMode } = useColorMode();
  const [fileNames, setFileNames] = useState(
    Array(assignments.length).fill("") as string[]
  );
  const [fileStatus, setFileStatus] = useState(
    Array(assignments.length).fill("Not Submitted") as (
      | "Correct"
      | "Incorrect"
      | "Submitting"
      | "Not Submitted"
    )[]
  );
  const [solutions, setSolutions] = useState(
    Array(assignments.length).fill(null) as (CodeReturn | null)[]
  );

  const handleSolutions = (output: CodeReturn | null, index: number) => {
    const temp = solutions.concat();
    temp[index] = output;
    setSolutions(temp);
  };

  const onUploadFile = async (formData: FormData, index: number) => {
    formData.append("dest", assignments[index].folder);
    const temp: string[] = fileNames.concat();
    temp[index] = (formData.get("file") as File).name;
    setFileNames(temp);
    const tem = fileStatus.concat();
    tem[index] = "Submitting";
    handleSolutions(null, index);
    setFileStatus(tem);
    const { data }: { data: UploadPostRes } = await axios.post(
      "/api/uploads",
      formData,
      {}
    );
    const tempt = fileStatus.concat();
    tempt[index] = data.returns.isCorrect ? "Correct" : "Incorrect";
    setFileStatus(tempt);
    handleSolutions(data.returns, index);
    if (data.returns.warnings.length > 0) {
      setWarnings(data.returns.warnings);
      onWarningsOpen();
    }
  };
  return (
    <Box>
      <Flex p={3}>
        <Spacer />
        <Button onClick={toggleColorMode}>
          {colorMode === "dark" ? <SunIcon /> : <MoonIcon />}
        </Button>
      </Flex>
      <Box mb={8} w="full" p={4}>
        {assignments.map((assignment, i) => {
          return (
            <AssignmentBox
              assignment={assignment}
              colorMode={colorMode}
              filename={fileNames[i]}
              solution={solutions[i]}
              status={fileStatus[i]}
              handleSolutions={handleSolutions}
              onUploadFile={onUploadFile}
              index={i}
            />
          );
        })}
      </Box>
      <WarningModal
        isOpen={warningsOpen}
        warnings={warnings}
        onClose={onWarningsClose}
      />
    </Box>
  );
};

export const getServerSideProps: GetServerSideProps<IProps> = async () => {
  return {
    props: {
      assignments: getAssignments(),
    },
  };
};

Home.propTypes = {
  assignments: PropTypes.arrayOf(
    PropTypes.shape({
      name: PropTypes.string.isRequired,
      desc: PropTypes.string.isRequired,
      folder: PropTypes.string.isRequired,
      order: PropTypes.number.isRequired,
    })
  ).isRequired as React.Validator<Assignment[]>,
};

export default Home;
