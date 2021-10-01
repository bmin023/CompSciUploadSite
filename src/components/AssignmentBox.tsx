import { CloseIcon } from "@chakra-ui/icons";
import {
  Box,
  Divider,
  Flex,
  VStack,
  HStack,
  Code,
  Text,
  ColorMode,
  Button,
} from "@chakra-ui/react";
import React from "react";

import { Assignment, CodeReturn } from "utils/assignmentUtils";

import { FileUpload } from "./otherUploader";

interface AssignmentProps {
  assignment: Assignment;
  solution: CodeReturn | null;
  status: "Correct" | "Incorrect" | "Submitting" | "Not Submitted";
  colorMode: ColorMode;
  filename: string;
  handleSolutions: (solution: CodeReturn | null, index: number) => void;
  onUploadFile: (form: FormData, index: number) => void;
  index: number;
}

const AssignmentBox: React.FC<AssignmentProps> = ({
  assignment,
  solution,
  status,
  colorMode,
  filename,
  handleSolutions,
  onUploadFile,
  index,
}) => {
  const getColor = (): string => {
    if (solution) {
      if (solution.isCorrect) {
        return "green.400";
      }
      return "red.400";
    }
    if (colorMode === "dark") {
      return "white";
    }
    return "black";
  };

  return (
    <Box p={2} key={assignment.order}>
      <Divider m={2} size="10px" />
      <Text my={2} fontSize="xl" fontWeight="bold" textAlign="center">
        {`${assignment.order}: ${assignment.name}`}:&nbsp;
        <Text as="span" fontSize="xl" fontWeight="extrabold" color={getColor()}>
          {status}
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
          index={index}
          onUpload={onUploadFile}
          my={2}
          colorScheme="blue"
        >
          {filename.length > 0 ? filename : "Upload File"}
        </FileUpload>
        {(
          solution
            ? solution && (solution as CodeReturn).solution.length > 0
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
                  isCorrect: solution?.isCorrect || false,
                  solution: [],
                  student: [],
                  warnings: [],
                },
                index
              );
            }}
          >
            Clear Results
          </Button>
        ) : null}
      </Flex>
      {solution ? (
        <VStack p={1}>
          {solution?.solution.map((code, j) => {
            const student = solution?.student[j];
            return (
              <HStack m={0.25} spacing={2}>
                <Code p={1} sx={{ whiteSpace: "pre-line" }}>
                  {code}
                </Code>
                <Code
                  p={1}
                  colorScheme={
                    code.replace(/\s+/g, "") === student?.replace(/\s+/g, "")
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
};

export default AssignmentBox;
