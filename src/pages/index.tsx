import { Box, Button, Code, Divider, Flex, HStack, Spacer, Text, useColorMode, useDisclosure, VStack } from "@chakra-ui/react";
import axios from "axios";
import { FileUpload } from "components/otherUploader";
import { GetServerSideProps, NextPage } from "next";
import React, { useState } from "react";
import { Assignment, CodeReturn, getAssignments } from "utils/assignmentUtils";
import { UploadPostRes } from "./api/uploads";
import { CloseIcon, SunIcon, MoonIcon } from '@chakra-ui/icons';
import { WarningModal } from "components/WarningModal";

const Home: NextPage<{ assignments: Assignment[] }> = (props) => {
  const { isOpen: warningsOpen, onClose: onWarningsClose, onOpen: onWarningsOpen } = useDisclosure();
  const [warnings,setWarnings] = useState([] as string[])
  const {colorMode,toggleColorMode} = useColorMode();
  const [fileNames, setFileNames] = useState(
    Array(props.assignments.length).fill("") as string[]
  );
  const [fileStatus, setFileStatus] = useState(
    Array(props.assignments.length).fill("Not Submitted") as (
      | "Correct"
      | "Incorrect"
      | "Submitting"
      | "Not Submitted"
    )[]
  );
  const [solutions, setSolutions] = useState(
    Array(props.assignments.length).fill(null) as (CodeReturn | null)[]
  );

  const handleSolutions = (output: CodeReturn | null, index: number) => {
    const temp = solutions.concat();
    temp[index] = output;
    setSolutions(temp);
  };

  const onUploadFile = async (formData: FormData, index: number) => {
    formData.append("dest", props.assignments[index].folder);
    let temp: string[] = fileNames.concat();
    temp[index] = (formData.get("file") as File).name;
    setFileNames(temp);
    let tem = fileStatus.concat();
    tem[index] = "Submitting";
    handleSolutions(null, index);
    setFileStatus(tem);
    const res = await axios.post("/api/uploads", formData, {});
    const data: UploadPostRes = res.data;
    let tempt = fileStatus.concat();
    tempt[index] = data.returns.isCorrect ? "Correct" : "Incorrect";
    setFileStatus(tempt);
    handleSolutions(data.returns, index);
    if (data.returns.warnings.length > 0) {
      setWarnings(data.returns.warnings);
      onWarningsOpen();
    }
    console.log("response", data);
  };
  return (
    <Box>
      <Flex p={3}>
        <Spacer />
        <Button onClick={toggleColorMode}>
        {colorMode === "dark" ? <SunIcon /> : <MoonIcon />}
      </Button></Flex>
      <Box mb={8} w="full" p={4}>
        {props.assignments.map((assignment, i) => {
          return (
            <Box p={2} key={assignment.order}>
              <Divider m={2} size="10px" />
              <Text my={2} fontSize="xl" fontWeight="bold" textAlign="center">
                {assignment.order + ". " + assignment.name}:&nbsp;
                <Text
                  as="span"
                  fontSize="xl"
                  fontWeight="extrabold"
                  color={
                    solutions[i]
                      ? solutions[i]?.isCorrect
                        ? "green.400"
                        : "red.400"
                      : colorMode === "dark"
                      ? "white"
                      : "black"
                  }
                >
                  {fileStatus[i]}
                </Text>
              </Text>
              <Text
                sx={{ whiteSpace: "pre-line" }}
                fontSize="md"
                fontWeight="light"
                mx="auto"
                w="60%"
                textAlign="center"
              >
                {assignment.desc}
              </Text>
              <Flex my={2} mx="auto" w="fit-content">
                <FileUpload
                  index={i}
                  onUpload={onUploadFile}
                  my={2}
                  colorScheme="blue"
                >
                  {fileNames[i].length > 0 ? fileNames[i] : "Upload File"}
                </FileUpload>
                {(
                  solutions[i]
                    ? solutions[i] &&
                      (solutions[i] as CodeReturn).solution.length > 0
                    : false
                ) ? (
                  <Button
                    m={2}
                    leftIcon={<CloseIcon />}
                    variant="outline"
                    colorScheme="red"
                    onClick={() => {
                      handleSolutions(
                        {
                          isCorrect: solutions[i]?.isCorrect ? true : false,
                          solution: [],
                          student: [],
                          warnings: [],
                        },
                        i
                      );
                    }}
                  >
                    Clear Results
                  </Button>
                ) : null}
              </Flex>
              {solutions[i] ? (
                <VStack p={1}>
                  {solutions[i]?.solution.map((code, j) => {
                    let student = solutions[i]?.student[j];
                    return (
                      <HStack m={0.25} spacing={2}>
                        <Code p={1} sx={{ whiteSpace: "pre-line" }}>
                          {code}
                        </Code>
                        <Code
                          p={1}
                          colorScheme={
                            code.replace(/\s+/g, "") ===
                            student?.replace(/\s+/g, "")
                              ? "green"
                              : "red"
                          }
                          sx={{ whiteSpace: "pre-line" }}
                        >
                          {student}
                        </Code>
                      </HStack>
                    );
                  })}
                </VStack>
              ) : null}
            </Box>
          );
        })}
      </Box>
      <WarningModal isOpen={warningsOpen} warnings={warnings} onClose={onWarningsClose} onOpen={onWarningsOpen} />
    </Box>
  );
};

export const getServerSideProps: GetServerSideProps = async () => {
  return {
    props: {
      assignments: getAssignments(),
    },
  };
};

export default Home;
